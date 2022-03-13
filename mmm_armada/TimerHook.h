#pragma once

#include "Hook.h"

namespace mmm
{
	class TimerHook
		: public Hook
	{
	public:
		explicit TimerHook( const std::string& id, luabind::object table, 
			luabind::object function, luabind::object argument );
	};

	void timerhook_register( lua_State* state );
}
