#include "UtritiumBallClass_Internal.h"

namespace mmm
{
	void
	utritiumballclass_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<UtritiumBallClass, TerrainObjectClass, GameObjectClassPtr>( "UtritiumBallClass" )
				.property( "damage", &UtritiumBallClass::getDamage, &UtritiumBallClass::setDamage )
				.property( "radius", &UtritiumBallClass::getRadius, &UtritiumBallClass::setRadius )
				.property( "rotation", &UtritiumBallClass::getRotation, &UtritiumBallClass::setRotation )
				.property( "lifetime", &UtritiumBallClass::getLifetime, &UtritiumBallClass::setLifetime )
				.property( "scalingStepSize", &UtritiumBallClass::getScalingStepSize, &UtritiumBallClass::setScalingStepSize )
				.property( "scalingCount", &UtritiumBallClass::getScalingCount, &UtritiumBallClass::setScalingCount )
		];
	}
}
