#pragma once

#include "Hook.h"

namespace mmm
{
	class MonitorHook
		: public Hook
	{
	public:
		enum Type
		{
			OnTrue = 0,
			OnFalse,
			WhileTrue,
			WhileFalse,
			OnStop
		};
		
		explicit MonitorHook( const std::string& id, luabind::object table, 
			luabind::object function, luabind::object argument, Type type );

		Type getType() const;

		void setType( Type type );
	private:
		Type type_;
	};

	void monitorhook_register( lua_State* state );
}
