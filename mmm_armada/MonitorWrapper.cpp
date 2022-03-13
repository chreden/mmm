#include "MonitorWrapper.h"

namespace mmm
{
	MonitorWrapper::MonitorWrapper( const std::string& id, bool initialState, luabind::object table,
									luabind::object function, luabind::object arg )
		: monitor_( Monitor::add( id, initialState, table, function, arg ) )
	{
		
	}

	MonitorWrapper::MonitorWrapper( MonitorPtr monitor )
		: monitor_( monitor )
	{

	}

	const std::string
	MonitorWrapper::getID( ) const
	{
		return monitor_->getID();
	}

	void
	MonitorWrapper::stop() 
	{
		monitor_->stop();
	}

	void
	MonitorWrapper::addHook( const std::string& id, MonitorHook::Type hookType, luabind::object table, luabind::object function,
						  luabind::object arg )
	{
		monitor_->addHook( id, hookType, table, function, arg );
	}

	bool
	MonitorWrapper::unhook( const std::string& id )
	{
		return monitor_->unhook( id );
	}

	bool
	MonitorWrapper::unhook( HookPtr hook )
	{
		return monitor_->unhook( hook );
	}

	luabind::object 
	MonitorWrapper::getHooks() const
	{
		return monitor_->getHooks();
	}

	bool 
	MonitorWrapper::getState() const
	{
		return monitor_->getState();
	}
}

