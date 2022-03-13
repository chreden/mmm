#include "Timer.h"
#include "Game_Internal.h"
#include "ScriptErrors.h"
#include "TimerWrapper.h"
#include "TimerHook.h"

namespace mmm
{
	namespace 
	{
		std::vector<TimerPtr> timers;
	}

	Timer::Timer( const std::string& id, float interval, State state )
			: id_( id ),
			  interval_( interval ),
			  state_( state ), 
			  startTime_( Game().getTime() ),
			  repeat_( false )
	{

	}

	const std::string&
	Timer::getId() const
	{
		return id_;
	}

	float			   
	Timer::getInterval() const
	{
		return interval_;
	}

	bool
	Timer::getRepeat( ) const
	{
		return repeat_;
	}

	float			   
	Timer::getStartTime() const
	{
		return startTime_;
	}

	bool
	Timer::getStarted() const
	{
		return state_ == State_Started;
	}

	Timer::State					
	Timer::getState() const
	{
		return state_;
	}

	void			   
	Timer::setInterval( float value )
	{
		interval_ = value;
	}

	void
	Timer::setRepeat( bool value )
	{
		repeat_ = value;
	}

	void			   
	Timer::tick()
	{
		if( !hooks_.empty( ) ) 
		{
			TimerWrapper wrapper( shared_from_this() );

			auto hooksCopy = hooks_;
			for( auto iter = hooksCopy.begin(); iter != hooksCopy.end(); ++iter )
			{
				try
				{
					HookPtr hook = iter->second;

					luabind::object table = hook->getTable();

					if( table && table.is_valid() )
					{
						luabind::call_function<void>( hook->getFunction(), table, wrapper, hook );
					}
					else
					{
						luabind::call_function<void>( hook->getFunction(), wrapper, hook );
					}
				}
				catch( const luabind::error& )
				{
					scriptError( std::string( "Error in Timer.tick : " ) + lua_tostring( common::Storage::instance().mainLuaVM, -1  ) );
				}
			}
		}

		if( getRepeat() )
		{
			start();
		}
		else
		{
			stop();
		}
	}

	void
	Timer::start( )
	{
		state_		= State_Started;
		startTime_	= Game().getTime();

		//Check to see if the timer is in the active list - if it isn't we have to add it so that
		//it gets updated. This means that people can hang on to timers if they want.
		TimerPtr timer = shared_from_this();
		if( std::find( timers.begin(), timers.end(), timer ) == 
			timers.end() )
		{
			timers.push_back( timer );
		}
	}

	void
	Timer::stop( )
	{
		//Stop the timer
		state_ = State_Stopped;
		//Remove it from the active list, if it is there
		std::remove( timers.begin(), timers.end(), shared_from_this() );
	}

	bool
	Timer::hook( const std::string& id, luabind::object table, luabind::object function, luabind::object arguments )
	{
		if( hooks_.find( id ) != hooks_.end() )
		{
			return false;
		}
		hooks_[ id ] = HookPtr( new TimerHook( id, table, function, arguments ) );
		return true;
	}

	bool
	Timer::unhook( const std::string& id )
	{
		auto iter = hooks_.find( id );
		if( iter != hooks_.end() )
		{
			hooks_.erase( iter );
			return true;
		}
		return false;
	}

	bool					
	Timer::unhook( HookPtr hook )
	{
		if( !hook )
		{
			return false;
		}
		
		auto iter = hooks_.find( hook->getId() );
		if( iter == hooks_.end() )
		{
			return false;
		}

		hooks_.erase( iter );
		return true;
	}

	luabind::object			
	Timer::getHooks() const
	{
		luabind::object results = luabind::newtable(common::Storage::instance().mainLuaVM);
		for( auto iter = hooks_.begin(); iter != hooks_.end(); ++iter )
		{
			results[iter->first] = HookPtr( iter->second );
		}	
		return results;
	}

	void 
	timer_update( )
	{
		common::Storage& storage( common::Storage::instance( ) );
		lua_State* state = storage.mainLuaVM;

		std::vector<TimerPtr> timersCopy( timers );

		float currentTime = Game().getTime( );

		for( std::size_t i = 0; i < timersCopy.size( ); ++i )
		{
			if( timersCopy[i]->getStarted() )
			{
				if( currentTime - timersCopy[i]->getStartTime() >= timersCopy[i]->getInterval() )
				{
					try
					{
						timersCopy[i]->tick();
					}
					catch( const luabind::error& )
					{
						scriptError( std::string( "Error in Timers.update : " ) + lua_tostring( state, -1  ) );
					}
				}
			}
		}
	}

	TimerPtr 
	Timer::add( const std::string& id, float interval, State started )
	{
		TimerPtr newTimer( new Timer( id, interval, started ) );
		timers.push_back( newTimer );
		return newTimer;
	}

	luabind::object
	Timer::getAll()
	{
		luabind::object results = luabind::newtable(common::Storage::instance().mainLuaVM);
		const std::size_t Count = timers.size();
		for( std::size_t i = 0; i < Count; ++i ) 
		{
			results[i+1] = TimerWrapperPtr( new TimerWrapper(timers[i]) );
		}
		return results;
	}

	TimerWrapperPtr 
	Timer::find(const std::string& id)
	{
		const std::size_t Count = timers.size();
		for( std::size_t i = 0; i < Count; ++i )
		{
			if( timers[i]->getId() == id )
			{
				return TimerWrapperPtr( new TimerWrapper( timers[i]) );
			}
		}
		return TimerWrapperPtr();
	}

	void
	Timer::stopAll() 
	{
		//Using the stop function would be slower, so stopping the timers manually here
		//and then removing everything.
		std::for_each( timers.begin(), timers.end(),
			[] (TimerPtr timer) 
		{
			timer->state_ = Timer::State_Stopped;
		});
		timers.clear();
	}
}