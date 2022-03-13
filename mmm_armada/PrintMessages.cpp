#include "PrintMessages.h"
#include "Game_Internal.h"
#include "UI_Internal.h"
#include "Debug_Internal.h"
#include "DebuggerConnection.h"

namespace mmm
{
	std::vector<std::pair<int,float>> PrintMessages::messages_( 20, std::make_pair(0,-10) );
	int								  PrintMessages::currentIndex_;

	void
	PrintMessages::add( const std::string& message, DebuggerConnection::Type type )
	{
		//If we have a connection we should send the message on.
		if( DebuggerConnection::getInstance().connected() )
		{
			DebuggerConnection::getInstance().sendMessage( message, type );
		}
		else
		{
			//Right, we have a number of messages. We add them, and store a time.
			//When this time expires, the thing becomes available again.
			std::size_t newIndex = getIndex( );

			int id = UI().addMessage( message, 50, 50 + 30 * newIndex, JUSTIFY_TOP_LEFT, ST3D_Colour( 0xffffffff ), false, 1e6 );

			if( newIndex == messages_.size( ) )
			{
				messages_.push_back( std::make_pair( id, Game().getTime( ) ) );
			}
			else
			{
				UI().removeMessage( messages_[ newIndex ].first );
				messages_[ newIndex ] = std::make_pair( id, Game().getTime( ) );
			}
		}
	}

	std::size_t
	PrintMessages::getIndex( )
	{
		float currentTime = Game().getTime( );

		if( currentIndex_ == messages_.size( ) - 1)
		{
			currentIndex_ = 0;
			//KILL EVERYTHING?
			std::for_each( messages_.begin( ), messages_.end( ), 
				[] (const std::pair<int, float>& o) { UI().removeMessage(o.first); } );
		}
		else
		{
			++currentIndex_;
		}

		return currentIndex_;
	}
}
