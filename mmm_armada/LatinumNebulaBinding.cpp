#include "LatinumNebula_Internal.h"

namespace mmm
{
	void
	latinumnebula_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<LatinumNebula, TerrainObject, EntityPtr>( "LatinumNebula" )
		];
	}
}
