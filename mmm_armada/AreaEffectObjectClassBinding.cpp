#include "AreaEffectObjectClass_Internal.h"

namespace mmm
{
	void
	areaeffectobjectclass_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<AreaEffectObjectClass, TerrainObjectClass, GameObjectClassPtr>( "AreaEffectObjectClass" )
				.property("radius", &AreaEffectObjectClass::getRadius, &AreaEffectObjectClass::setRadius )
		];
	}
}
