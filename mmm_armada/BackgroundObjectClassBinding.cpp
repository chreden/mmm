#include "BackgroundObjectClass_Internal.h"

namespace mmm
{
	void
	backgroundobjectclass_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<BackgroundObjectClass, TerrainObjectClass, GameObjectClassPtr>( "BackgroundObjectClass" )
		];
	}
}