#include "CraftSystem_Internal.h"

namespace mmm
{
	void
	craftsystem_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<CraftSystem, CraftSystemPtr>( "CraftSystem" )
				.property( "active", &CraftSystem::getActive, &CraftSystem::setActive )
				.property( "permanentDisable", &CraftSystem::getPermanentDisable, &CraftSystem::setPermanentDisable )
				.property( "hitpoints", &CraftSystem::getHitpoints, &CraftSystem::setHitpoints )
				.property( "health", &CraftSystem::getHealth, &CraftSystem::setHealth )
				.property( "maxHitpoints", &CraftSystem::getMaxHitpoints, &CraftSystem::setMaxHitpoints )
		];
	}
}

