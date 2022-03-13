#include "Game_Internal.h"
#include "Type_Team.h"
#include "MemRaider.h"
#include "Type_ST3D_GraphicsEngine.h"
#include "Type_ST3D_Device.h"

namespace mmm
{
	namespace
	{
		const std::size_t Address_GetTime		= 0x0065f740;
		const std::size_t Address_AllowWarp		= 0x006f4de0;
		const std::size_t Address_GTransport	= 0x0076b8d4;
		const std::size_t Address_GetGameSetup	= 0x00557930;
		const std::size_t Address_GetMapTitle	= 0x00546240;
		const std::size_t Address_IsHost		= 0x00546de0;
		const std::size_t Address_Transport		= 0x0076b8d4;
		const std::size_t Address_GetLocalSlot	= 0x00547470;
		const std::size_t Address_GetGameSpeed	= 0x00558c70;
		const std::size_t Address_SetGameSpeed	= 0x00558c60;
	}

	float 
	Game::getTime( ) const
	{
		return memory_function< float(*)() >( Address_GetTime )( );
	}
		
	bool 
	Game::getAllowWarp( ) const
	{
		return static_cast<bool>( *reinterpret_cast<int*>( Address_AllowWarp ) );
	}

	bool
	Game::getAllowSave( ) const
	{
		return false;
	}
		
	float
	Game::getUpdateTime( ) const
	{
		return common::Storage::instance().updateTime;
	}

	const char*
	Game::getMapTitle( ) const
	{
		types::Transport* transport = LoadMemPointer< types::Transport >( Address_GTransport );

		const types::GameSetup& setup = 
			(transport->*memory_function< const types::GameSetup& (types::Transport::*)( ) >( Address_GetGameSetup ))( );

		//Now returning the map title.
		return (setup.*memory_function< const char* (types::GameSetup::*)( ) const >( Address_GetMapTitle ))( );
	}

	bool 
	Game::isHost( ) const
	{
		types::Transport* transport = LoadMemPointer< types::Transport >( Address_GTransport );

		const types::GameSetup& setup =
			(transport->*memory_function< const types::GameSetup& (types::Transport::*)( ) >( Address_GetGameSetup ))( );

		bool result = (setup.*memory_function< bool (types::GameSetup::*)( ) const >( Address_IsHost ))( );
		return result;
	}

	int
	Game::getSeed( ) const
	{
		return memraider::MrNode(Address_Transport).getInner().getInner(0x30).getInner(0x10).get<int>(0x28);
	}

	int
	Game::getLocalSlot( ) const
	{
		types::Transport* transport = LoadMemPointer< types::Transport >( Address_GTransport );
		types::GameSetup& setup =
			(transport->*memory_function< types::GameSetup& (types::Transport::*)( ) >( Address_GetGameSetup ))( );
		return (setup.*memory_function< int (types::GameSetup::*)( ) >( Address_GetLocalSlot ))( );
	}

	int
	Game::getGameSpeed( ) const
	{
		using namespace types;
		Transport* transport = LoadMemPointer< Transport >( Address_GTransport );
		return (transport->*memory_function< int (Transport::*)() >( Address_GetGameSpeed ))
					();
	}

	void
	Game::setGameSpeed( int value )
	{
		//Values of 0 or less confuse the game so they are not allowed, even though
		//those crazy people might want to set them.
		if( value < 1 )
		{
			return;
		}

		using namespace types;
		Transport* transport = LoadMemPointer< Transport >( Address_GTransport );
		return (transport->*memory_function< void (Transport::*)(int) >( Address_SetGameSpeed ))
					(value);
	}

	void 
	Game::setAllowSave( bool value )
	{
		value ? getScriptInterface( )->EnableSave( ) :
				getScriptInterface( )->DisableSave( );
	}
		
	void 
	Game::setAllowWarp( bool value )
	{
		*reinterpret_cast<int*>( Address_AllowWarp ) = value;
	}

	void 
	Game::setUpdateTime( float interval )
	{
		common::Storage::instance( ).updateTime = interval;
	}

	HWND		
	Game::getWindow() const
	{
		auto engine = types::getGraphicsEngine();
		if( !engine )
		{
			return 0;
		}
		auto device = engine->m_device[0];
		if( !device )
		{
			return 0;
		}
		return memraider::MrNode(device).get<HWND>(0xa8);
	}
}