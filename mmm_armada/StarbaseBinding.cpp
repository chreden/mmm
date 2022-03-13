#include "Starbase_Internal.h"

namespace mmm
{
	void
	starbase_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<Starbase, Shipyard, EntityPtr>( "Starbase" )
				
		];
	}
}
