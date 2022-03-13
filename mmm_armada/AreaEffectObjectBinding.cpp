#include "AreaEffectObject_Internal.h"

namespace mmm
{
	void 
	areaeffectobject_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<AreaEffectObject, TerrainObject, EntityPtr>( "AreaEffectObject" )
		];
	}
}
