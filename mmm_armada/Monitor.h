#pragma once

#include "MonitorHook.h"

namespace mmm
{
	/**
		A Monitor tracks the state of a condition by calling a user defined
		function. The user can attach hooks that will be called when the
		condition changes state.
	*/
	class Monitor
		: public boost::enable_shared_from_this<Monitor>
	{
	public:
		/**
			Add a hook to the monitor.
			@param id The unique identifier of the new hook.
			@param type The event to hook on to.
			@param table The table of the hook function.
			@param function The function to call.
			@param argument An argument for the function.
			@return True if the hook was created successfully.
		*/
		bool addHook( const std::string& id, MonitorHook::Type type, luabind::object table, 
			luabind::object function, luabind::object argument );
		/**
			Remove the specified hook from the monitor.
			@param id The id of the monitor to remove
		*/
		bool unhook( const std::string& id );
		/**
			Remove the specified hook from the monitor.
			@param hook The hook to remove.
		*/
		bool unhook( HookPtr hook );
		/**
			Stop the monitor. This will remove the monitor from the active
			monitors list.
		*/
		void stop( );
		/**
			Get the identifier of the Monitor.
			@return The id of the monitor.
		*/
		const std::string getID( ) const;
		/**
			Get the current state of the monitor's condition.
			@return The current condition state.
		*/
		bool getState() const;
		/**
			Get all registered hooks.
			@return A table of registered hooks.
		*/
		luabind::object getHooks() const;

		static MonitorPtr add( const std::string& id, bool initialState, luabind::object conditionTable, 
			luabind::object conditionFunction, luabind::object conditionArgument );
		
		static void		update( );
		
		static MonitorWrapperPtr find( const std::string& id );
		
		static luabind::object getAll();
		
		static void clear();
	private:
		Monitor( const std::string& id, bool initialState, luabind::object conditionTable, 
			luabind::object conditionFunction, luabind::object conditionArgument );

		bool	 test( );
		MonitorHook::Type selectHook( bool newValue ) const;
		void	 setState( bool value );
		void	 callHook( MonitorHook::Type hookType );
		void	testAndFire( );	

		std::unordered_map<std::string, MonitorHookPtr> hooks_;
		std::string									  id_;
		luabind::object								  conditionTable_;
		luabind::object								  conditionFunction_;
		luabind::object								  conditionArgument_;
		bool										  state_;
	};
}
