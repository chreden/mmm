#include "BackgroundPlanet_Internal.h"

namespace mmm
{
	void
	backgroundplanet_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<BackgroundPlanet, BackgroundObject, EntityPtr>( "BackgroundPlanet" )
		];
	}
}
