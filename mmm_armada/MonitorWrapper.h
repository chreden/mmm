#pragma once

#include "Monitor.h"

namespace mmm
{
	class MonitorWrapper
	{
	public:
		explicit MonitorWrapper( const std::string& id, bool initialState, luabind::object table,
						luabind::object function, luabind::object arg );
		explicit MonitorWrapper( MonitorPtr monitor );
		
		void			  addHook( const std::string& id, MonitorHook::Type type, luabind::object table, 
								   luabind::object function, luabind::object arg );

		bool unhook( const std::string& id );

		bool unhook( HookPtr hook );

		luabind::object getHooks() const;

		void			  stop( );
		const std::string getID( ) const;

		bool getState() const;
	private:
		MonitorPtr monitor_;
	};

	void monitor_register( lua_State* state );
}
