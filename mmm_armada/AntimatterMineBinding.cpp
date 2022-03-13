#include "AntimatterMine.h"

namespace mmm
{
	void
	antimattermine_register( lua_State* state )
	{
		using namespace luabind;
		module(state)
		[
			class_<AntimatterMine, Mine, EntityPtr>( "AntimatterMine" )
		];
	}
}