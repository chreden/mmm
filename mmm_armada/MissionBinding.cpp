#include "Mission_Internal.h"

namespace mmm
{
	namespace
	{
		Mission mission;
	}

	void
	mission_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<Mission>( "_Mission" )
				.def( "finish", &Mission::end )
		];

		globals(state)["Mission"] = &mission;
	}
}
