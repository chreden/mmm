#include "Monitor.h"
#include "ScriptErrors.h"
#include "MonitorWrapper.h"
#include "MonitorHook.h"

namespace mmm
{
	namespace
	{
		std::vector<MonitorPtr> monitors_;
	}

	Monitor::Monitor( const std::string& id, bool initialState, luabind::object conditionTable, 
		luabind::object conditionFunction, luabind::object conditionArgument )
		: id_(id), conditionTable_( conditionTable ), conditionFunction_( conditionFunction ),
			conditionArgument_( conditionArgument ), state_( initialState )
	{
			
	}

	MonitorPtr
	Monitor::add( const std::string& id, bool initialState, luabind::object conditionTable, 
			luabind::object conditionFunction, luabind::object conditionArgument )
	{
		MonitorPtr newMonitor( new Monitor( id, initialState, conditionTable, conditionFunction, conditionArgument ) );
		monitors_.push_back( newMonitor );
		return newMonitor;
	}

	const std::string
	Monitor::getID() const
	{
		return id_;
	}

	bool
	Monitor::addHook( const std::string& id, MonitorHook::Type type, luabind::object table, luabind::object function, luabind::object argument )
	{
		//Search through the hooks to see if we already have something with this id.
		if( hooks_.find( id ) != hooks_.end() )
		{
			return false;
		}
		hooks_[id]= MonitorHookPtr( new MonitorHook( id, table, function, argument, type ) );
		return true;
	}

	bool
	Monitor::unhook( const std::string& id ) 
	{
		auto iter = hooks_.find( id );
		if( iter == hooks_.end() )
		{
			return false;
		}
		hooks_.erase( iter );
		return true;
	}

	bool
	Monitor::unhook( HookPtr hook )
	{
		auto iter = std::find_if( hooks_.begin(), hooks_.end(),
					[&](const std::pair<std::string, MonitorHookPtr>& hookIter)
						{
							return hookIter.second == hook;
						} );
		if( iter == hooks_.end() )
		{
			return false;
		}
		hooks_.erase( iter );
		return true;
	}

	luabind::object 
	Monitor::getHooks() const
	{
		luabind::object results = luabind::newtable( common::Storage::instance().mainLuaVM );
		for( auto iter = hooks_.begin();
			 iter != hooks_.end();
			 ++iter )
		{
			results[iter->first] = HookPtr( iter->second );
		}
		return results;
	}

	void
	Monitor::testAndFire( )
	{
		bool newState		= test();
		MonitorHook::Type hookType	= selectHook( newState );
		setState( newState );
		callHook( hookType );
	}

	bool 
	Monitor::test( )
	{
		try
		{
			if( conditionTable_.is_valid( ) &&
				luabind::type( conditionTable_ ) != LUA_TNIL )
			{
				return luabind::call_function<bool>( conditionFunction_, conditionTable_, MonitorWrapper(shared_from_this()), conditionArgument_ );
			}
			return luabind::call_function<bool>( conditionFunction_, MonitorWrapper(shared_from_this()), conditionArgument_ );
		}
		catch( const luabind::error& )
		{
			scriptError( std::string( "Error in monitor condition function : " ) + lua_tostring(common::Storage::instance().mainLuaVM, -1) );
		}
		return false;
	}

	MonitorHook::Type 
	Monitor::selectHook( bool newValue ) const
	{
		if( newValue == state_ )
		{
			if( state_ )
			{
				return MonitorHook::WhileTrue;
			}
			else
			{
				return MonitorHook::WhileFalse;
			}
		}
			
		if( newValue )
		{
			return MonitorHook::OnTrue;
		}
		return MonitorHook::OnFalse;
	}

	void 
	Monitor::stop( )
	{
		//Inform listeners that we are about to be destroyed.
		callHook( MonitorHook::OnStop );

		//Actually proceed with the destruction of ourself.
		auto iter = std::find( monitors_.begin(), monitors_.end(), shared_from_this() );
		if( iter != monitors_.end() )
		{
			monitors_.erase( iter );
		}
	}

	bool 
	Monitor::getState() const
	{
		return state_;
	}

	void
	Monitor::setState( bool value )
	{
		state_ = value;
	}

	void	 
	Monitor::callHook( MonitorHook::Type hookType )
	{
		//Similar to updating the monitors, we take a copy of the hooks
		//here so they can be removed during updating.
		auto hooksCopy = hooks_;
		for( auto hookIter = hooksCopy.begin(); hookIter != hooksCopy.end(); ++hookIter )
		{
			MonitorHookPtr hook = hookIter->second;
			if( hook && hook->getType() == hookType )
			{
				try
				{
					if( hook->getTable().is_valid() && hook->getTable() )
					{
						luabind::call_function<void>( hook->getFunction(), hook->getTable(), MonitorWrapper( shared_from_this() ), hook );
					}
					else
					{
						luabind::call_function<void>( hook->getFunction(), MonitorWrapper( shared_from_this() ), hook );
					}
				}
				catch ( luabind::error& ) 
				{
					scriptError( std::string( "Error in Monitor Hook (" + id_ + "):(" + hook->getId() + ") : " ) + lua_tostring(common::Storage::instance().mainLuaVM, -1) );
				}
			}
		}
	}

	void 
	Monitor::update( )
	{
		//Copying the vector here so that we can add and remove safely from
		//the vector during monitor iteration. Saves a lot of messing around.
		std::vector<MonitorPtr> monitors = monitors_;
		for( std::size_t i = 0; i < monitors.size(); ++i )
		{
			monitors[i]->testAndFire();
		}
	}

	MonitorWrapperPtr
	Monitor::find( const std::string& id )
	{
		const std::size_t Count = monitors_.size();
		for( std::size_t i = 0; i < Count; ++i )
		{
			if( monitors_[i]->getID() == id )
			{
				return MonitorWrapperPtr( new MonitorWrapper( monitors_[i]) );
			}
		}
		return MonitorWrapperPtr();
	}

	luabind::object 
	Monitor::getAll()
	{
		luabind::object results = luabind::newtable(common::Storage::instance().mainLuaVM);
		const std::size_t Count = monitors_.size();
		for( std::size_t i = 0; i < Count; ++i ) 
		{
			results[i+1] = MonitorWrapper( monitors_[i] );
		}
		return results;
	}

	void 
	Monitor::clear()
	{
		monitors_.clear();
	}
}
