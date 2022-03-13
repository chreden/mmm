#include "BlackHole_Internal.h"

namespace mmm
{
	void
	blackhole_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<BlackHole, AreaEffectObject, EntityPtr>( "BlackHole" )
		];
	}
}
