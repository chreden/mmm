#include "TerrainObject_Internal.h"

namespace mmm
{
	void 
	terrainobject_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<TerrainObject, GameObject, EntityPtr>( "TerrainObject" )
		];
	}
}
