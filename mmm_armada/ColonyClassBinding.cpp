#include "ColonyClass_Internal.h"

namespace mmm
{
	void
	colonyclass_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<ColonyClass, CraftClass, EntityPtr>( "ColonyClass" )
		];
	}
}
