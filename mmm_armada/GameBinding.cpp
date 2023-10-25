#include "Game_Internal.h"

namespace mmm
{
	namespace
	{
		Game game;
	}

	void
	game_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<Game>("Game_")
				.property( "time", &Game::getTime )
				.property( "allowWarp", &Game::getAllowWarp, &Game::setAllowWarp )
				.property( "allowSave", &Game::getAllowSave, &Game::setAllowSave )
				.property( "updateTime", &Game::getUpdateTime, &Game::setUpdateTime )
				.property( "isHost", &Game::isHost )
				.property( "seed", &Game::getSeed )
				.property( "localSlot", &Game::getLocalSlot )
				.property( "gameSpeed", &Game::getGameSpeed, &Game::setGameSpeed )
				.property("ferengiCanSteal", &Game::getFerengiCanSteal, &Game::setFerengiCanSteal)
				.property("ferengiCanTrade", &Game::getFerengiCanTrade, &Game::setFerengiCanTrade)
		];

		globals(state)["Game"] = &game;
	}
}
