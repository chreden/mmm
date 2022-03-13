#include "DebuggerConnection.h"
#include "ScriptErrors.h"

namespace mmm
{
	DebuggerConnection::DebuggerConnection( )
		: socket_( 0 )
	{

	}

	DebuggerConnection::~DebuggerConnection( )
	{
		disconnect();
	}
	
	DebuggerConnection&
	DebuggerConnection::getInstance()
	{
		static DebuggerConnection connection;
		return connection;
	}
	
	bool 
	DebuggerConnection::connected() const
	{
		return socket_ != 0;
	}

	bool
	DebuggerConnection::connect( const std::string& ip, int port )
	{
		disconnect();

		WSADATA data;
		memset( &data, 0, sizeof(data) );
		if( WSAStartup( MAKEWORD( 2, 2 ), &data ) )
		{
			return false;
		}

		socket_ = socket(AF_INET, SOCK_STREAM, 0);

		sockaddr_in target;
		target.sin_family = AF_INET;
		target.sin_port = htons(6000);
		target.sin_addr.s_addr = inet_addr(ip.c_str());

		unsigned long mode = 1;
		ioctlsocket( socket_, FIONBIO, &mode );

		int error = 0;
		do
		{
			error = ::connect(socket_, (sockaddr*)&target, sizeof(target));
		
		} while( error && WSAGetLastError() == WSAEWOULDBLOCK );
		
		if( error && WSAGetLastError() != WSAEISCONN )
		{
			closesocket(socket_);
			socket_ = 0;
			WSACleanup();
			return false;
		}

		return true;
	}

	void
	DebuggerConnection::disconnect( )
	{
		if( connected() )
		{
			closesocket(socket_);
			socket_ = 0;
			WSACleanup();
		}
	}

	void
	DebuggerConnection::sendMessage( const std::string& message, DebuggerConnection::Type type )
	{
		//Try and send the message straight away. If we can't get away with it, we'll just
		//store it for next time.
		Message newMessage;
		newMessage.message  = message;
		newMessage.type		= type;

		if( !innerSend( newMessage ) )
		{
			messages_.push( newMessage );
		}
	}

	bool 
	DebuggerConnection::innerSend( const Message& message )
	{
		//Write message. +8 to size as we also have the type marker
		//and the string length marker to store.
		std::vector<char> buffer( message.message.size() + 8 );

		memcpy( &buffer[0], &message.type, sizeof(Type) );
		
		int size = message.message.size();
		memcpy(&buffer[4], &size, sizeof(int));
		memcpy(&buffer[8], message.message.c_str(), message.message.size());

		int result = send( socket_, &buffer[0], buffer.size(), 0 );
		if( result == SOCKET_ERROR ) 
		{
			return false;
		}
		return true;
	}

	void 
	DebuggerConnection::executeCommands( )
	{
		lua_State* state = common::Storage::instance().mainLuaVM;
		while( !commands_.empty() )
		{
			std::string command = commands_.front();
			commands_.pop();
			
			if( luaL_dostring( state, command.c_str() ) )
			{
				//Execute command, but don't want to stop execution if it fails.
				scriptError( std::string("Error in Debug : ") + lua_tostring(state, -1),
							 false );
			}
		}
	}

	void 
	DebuggerConnection::update( )
	{
		//Try and send messages (until one fails, when we will just abort)
		while( !messages_.empty() )
		{
			const Message& topMessage = messages_.front();
			if( innerSend( topMessage ) )
			{
				messages_.pop();
			}
			else
			{
				break;
			}
		}

		//Try and receive messages
		int length = 0;
		if( SOCKET_ERROR != recv( socket_, reinterpret_cast<char*>( &length ), sizeof(int), 0 ) )
		{
			std::vector<char> buffer( length );
			if( length > 0 && SOCKET_ERROR != recv( socket_, &buffer[0], length, 0 ) )
			{
				commands_.push( std::string( buffer.begin(), buffer.end() ) );
			}
		}
		
		executeCommands();
	}
}
