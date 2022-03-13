#include "TimerHook.h"

namespace mmm
{
	TimerHook::TimerHook( const std::string& id, luabind::object table, luabind::object function, luabind::object argument )
		: Hook( id, table, function, argument )
	{

	}

	void
	timerhook_register( lua_State* state )
	{
		using namespace luabind;
		module(state)
		[
			class_<TimerHook, Hook, HookPtr>( "TimerHook" )
		];
	}
}
