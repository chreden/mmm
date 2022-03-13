#include "TimerWrapper.h"

namespace mmm
{
	void
	timer_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<TimerWrapper, TimerWrapperPtr>( "Timer" )
				.def( constructor<const std::string&, float, Timer::State>() )
				.def( "hook", &TimerWrapper::hook )
				.def( "start", &TimerWrapper::start ) 
				.def( "stop", &TimerWrapper::stop )
				.def( "unhook", (bool (TimerWrapper::*)(const std::string&)) &TimerWrapper::unhook )
				.def( "unhook", (bool (TimerWrapper::*)(HookPtr)) &TimerWrapper::unhook )
				.property( "hooks", &TimerWrapper::getHooks )
				.property( "id", &TimerWrapper::getId )
				.property( "interval", &TimerWrapper::getInterval, &TimerWrapper::setInterval )
				.property( "repeats", &TimerWrapper::getRepeat, &TimerWrapper::setRepeat )
				.property( "state", &TimerWrapper::getState )
				.scope
				[
					def( "find", &Timer::find ),
					def( "getAll", &Timer::getAll ),
					def( "stopAll", &Timer::stopAll ),
					class_<Timer::State>("State")
						.enum_("constants")
						[
							value("Started", Timer::State_Started),
							value("Stopped", Timer::State_Stopped)
						]
				]
		];
	}
}
