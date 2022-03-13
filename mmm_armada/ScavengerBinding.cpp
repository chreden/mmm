#include "Scavenger.h"

namespace mmm
{
	void 
	scavenger_register( lua_State* state )
	{
		using namespace luabind;
		module(state)
		[
			class_<Scavenger, Craft, EntityPtr>( "Scavenger" )
		];
	}
}