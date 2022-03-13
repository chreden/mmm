#include "TerrainObjectClass_Internal.h"

namespace mmm
{
	void
	terrainobjectclass_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<TerrainObjectClass, GameObjectClass, GameObjectClassPtr>( "TerrainObjectClass" )
		];
	}
}