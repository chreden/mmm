#include "BackgroundPlanetClass_Internal.h"

namespace mmm
{
	void
	backgroundplanetclass_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<BackgroundPlanetClass, BackgroundObjectClass, GameObjectClassPtr>( "BackgroundPlanetClass" )
				.property( "rotationRate", &BackgroundPlanetClass::getRotationRate, &BackgroundPlanetClass::setRotationRate )
				.property( "crewModifier", &BackgroundPlanetClass::getCrewModifier, &BackgroundPlanetClass::setCrewModifier )
		];
	}
}
