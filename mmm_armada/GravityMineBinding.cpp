#include "GravityMine.h"

namespace mmm
{
	void
	gravitymine_register( lua_State* state )
	{
		using namespace luabind;
		module(state)
		[
			class_<GravityMine, Mine, EntityPtr>( "GravityMine" )
		];
	}
}
