#include "BackgroundObject_Internal.h"
#include "TerrainObject_Internal.h"
#include "Type_BackgroundObject.h"

namespace mmm
{
	void
	backgroundobject_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<BackgroundObject, TerrainObject, EntityPtr>( "BackgroundObject" )
		];
	}
}
