#include "TimerWrapper.h"

namespace mmm
{
	TimerWrapper::TimerWrapper( const std::string& id, float interval, Timer::State started )
		: timer_( Timer::add( id, interval, started ) )
	{

	}

	TimerWrapper::TimerWrapper( TimerPtr timer )
		: timer_( timer )
	{

	}

	const std::string
	TimerWrapper::getId( ) const
	{
		if( timer_ )
		{
			return timer_->getId();
		}
		return std::string();
	}

	float 
	TimerWrapper::getInterval() const
	{
		if( timer_ )
		{
			return timer_->getInterval();
		}
		return 0;
	}

	bool
	TimerWrapper::getRepeat() const
	{
		if( timer_ )
		{
			return timer_->getRepeat();
		}
		return false;
	}

	Timer::State	  
	TimerWrapper::getState() const
	{
		if( timer_ )
		{
			return timer_->getState();
		}
		return Timer::State_Stopped;
	}

	void 
	TimerWrapper::setInterval( float value )
	{
		if( timer_ )
		{
			timer_->setInterval( value );
		}
	}

	void
	TimerWrapper::setRepeat( bool value )
	{
		if( timer_ )
		{
			timer_->setRepeat( value );
		}
	}

	void
	TimerWrapper::start( )
	{
		if( timer_ )
		{
			timer_->start();
		}
	}

	void
	TimerWrapper::stop( )
	{
		if( timer_ )
		{
			timer_->stop();
		}
	}

	bool
	TimerWrapper::hook( const std::string& id,
						luabind::object table,
						luabind::object function,
						luabind::object arguments )
	{
		if( timer_ )
		{
			return timer_->hook( id, table, function, arguments );
		}
		return false;
	}

	bool
	TimerWrapper::unhook( const std::string& id )
	{
		if( timer_ )
		{
			return timer_->unhook( id );
		}
		return false;
	}

	bool			
	TimerWrapper::unhook( HookPtr hook )
	{
		if( hook )
		{
			return timer_->unhook( hook );
		}
		return false;
	}

	luabind::object 
	TimerWrapper::getHooks() const
	{
		if( timer_ )
		{
			return timer_->getHooks();
		}
		return luabind::object();
	}
}
