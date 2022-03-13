#include "LatinumNebulaClass_Internal.h"

namespace mmm
{
	void
	latinumnebulaclass_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<LatinumNebulaClass, TerrainObjectClass, GameObjectClassPtr>( "LatinumNebulaClass" )
				.property( "rotationSpeed", &LatinumNebulaClass::getRotationSpeed, &LatinumNebulaClass::setRotationSpeed )
		];
	}
}
