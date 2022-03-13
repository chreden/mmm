#include "MonitorWrapper.h"
#include "Monitor.h"

namespace mmm
{
	void
	monitor_register( lua_State* state )
	{
		using namespace luabind;
		module(state)
		[
			class_<MonitorWrapper>( "Monitor" )
				.def( constructor<std::string, bool, object, object, object>() )
				.def( "stop", &MonitorWrapper::stop )
				.def( "hook", &MonitorWrapper::addHook )
				.def( "unhook", (bool (MonitorWrapper::*)(const std::string&))&MonitorWrapper::unhook )
				.def( "unhook", (bool (MonitorWrapper::*)(HookPtr))&MonitorWrapper::unhook )
				.property( "id", &MonitorWrapper::getID )
				.property( "state", &MonitorWrapper::getState )
				.property( "hooks", &MonitorWrapper::getHooks )
				.scope
				[
					def("find", &Monitor::find ),
					def("getAll", &Monitor::getAll ),
					def("stopAll", &Monitor::clear )
				]
		];
	}
}
