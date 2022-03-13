#include "BlackHoleClass_Internal.h"

namespace mmm
{
	void
	blackholeclass_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<BlackHoleClass, AreaEffectObjectClass, GameObjectClassPtr>( "BlackHoleClass" )
				.property("gravityRadius", &BlackHoleClass::getGravityRadius, &BlackHoleClass::setGravityRadius )
				.property("eventRadius", &BlackHoleClass::getEventRadius, &BlackHoleClass::setEventRadius )
				.property("gravityForce", &BlackHoleClass::getGravityForce, &BlackHoleClass::setGravityForce )
				.property("rotation", &BlackHoleClass::getRotation, &BlackHoleClass::setRotation )
				.property("scaleSize", &BlackHoleClass::getScaleSize, &BlackHoleClass::setScaleSize )
		];
	}
}