#pragma once

namespace mmm
{
	class Timer;
	typedef boost::shared_ptr<Timer> TimerPtr;

	/**
		Repeatedly tick and call all hooked functions.
	*/
	class Timer 
		: public boost::enable_shared_from_this<Timer>
	{
	public:
		enum State
		{
			State_Stopped,
			State_Started
		};

		/**
			Get the Id of the Timer.
			@return The Id of the Timer.
		*/
		const std::string&		getId() const;
		/**
			Get the interval between ticks.
			@return The tick interval.
		*/
		float					getInterval() const;
		/**
			Get whether or not this timer will repeat.
			@return True if the timer repeats.
		*/
		bool					getRepeat() const;
		/**
			Get the time that this timer was started.
			@return The Armada time the timer started.
		*/
		float					getStartTime() const;
		/**
			Gets if the timer has been started.
			@return True if the timer is running.
		*/
		bool					getStarted() const;
		/**
			Set the tick interval.
			@param value The new tick interval.
		*/
		void					setInterval( float value );
		/**
			Set whether or not the timer should repeat.
			@param True to repeat.
		*/
		void					setRepeat( bool value );
		/**
			Add a hook function that will be called when the timer
			ticks.
			@return True if the timer was added.
		*/
		bool					hook( const std::string& id, 
									  luabind::object table, 
									  luabind::object function, 
									  luabind::object arguments );
		/**
			Remove a hook.
			@param id The id of the Timer to remove.
			@return True if the timer was removed.
		*/
		bool					unhook( const std::string& id );
		/**
			Unhook the specified hook.
			@param hook The hook to remove.
			@return True if the timer was removed.
		*/
		bool					unhook( HookPtr hook );
		/**
			Get all registered hooks.
			@return A table of hooks.
		*/
		luabind::object			getHooks() const;
		/**
			Get the current state of the Timer.
			@return The current state - a member of the State enum.
		*/
		State					getState() const;
		/**
			Start the timer ticking.
		*/
		void					start( );
		/**
			Stop the timer from ticking.
		*/
		void					stop( );
		/**
			Tick the timer.
		*/
		void					tick( );
		/**
			Create a new Timer.
			@param id The unique id of the new timer.
			@param interval The tick interval in seconds.
			@param state The initial state of the Timer.
			@return The new Timer, or null.
		*/
		static TimerPtr			add( const std::string& id, float interval, State state );
		/**
			Find an existing timer.
			@param id The id to search for.
			@return The Timer, or null if not found.
		*/
		static TimerWrapperPtr  find( const std::string& id );
		/**
			Stop all active timers.
		*/
		static void				stopAll( );
		/**
			Get all currently active timers.
			@return A table of all active Timers.
		*/
		static luabind::object  getAll();
	private:
		/**
			Create a new Timer.
			@param id The ID of the new Timer.
			@param interval Time between ticks.
			@param started Whether or not the timer is initially active.
		*/
		explicit Timer( const std::string& id, float interval, State state );

		std::unordered_map<std::string, HookPtr> hooks_;
		std::string						       id_;
		float							       interval_;
		float							       startTime_;
		bool							       repeat_;
		State							       state_;
	};

	void timer_update( );
	void timer_register( lua_State* state );
}
