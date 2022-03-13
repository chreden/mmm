#pragma once

#include "Timer.h"

namespace mmm
{
	class TimerWrapper
	{
	public:
		explicit TimerWrapper( const std::string& id, float interval, Timer::State started );
		
		explicit TimerWrapper( TimerPtr timer );

		const std::string getId() const;

		float			  getInterval() const;

		bool			  getRepeat() const;
		
		Timer::State	  getState() const;

		void			  setInterval( float value );

		void			  setRepeat( bool value );

		void			start( );

		void			stop( );

		/**
			
		*/
		bool			hook( const std::string& id,
							  luabind::object table,
							  luabind::object function,
							  luabind::object arguments );
		/**
			
		*/
		bool		    unhook( const std::string& id );

		bool			unhook( HookPtr hook );

		luabind::object getHooks() const;

	private:
		TimerPtr timer_;
	};
}
