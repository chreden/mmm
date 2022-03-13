#pragma once

namespace mmm
{
	/**
		
	*/
	class DebuggerConnection
	{
	public:

		enum Type
		{
			Type_Message,
			Type_Test,
			Type_Error
		};

		const static int DefaultPort = 6000;

		~DebuggerConnection( );

		static DebuggerConnection& getInstance();

		void sendMessage( const std::string& message, Type type );
		bool connected() const;
		bool connect( const std::string& ip, int port = DefaultPort );
		void disconnect( );
		void executeCommands( );

		void update( );
	private:
		DebuggerConnection( );

		struct Message
		{
			std::string message;
			Type		type;
		};

		bool innerSend( const Message& message );
		
		//Messages to be sent to the debugger.
		std::queue<Message>		messages_;
		
		std::queue<std::string> commands_;
		//TCP socket used to communicate.
		SOCKET					socket_;
	};
}
