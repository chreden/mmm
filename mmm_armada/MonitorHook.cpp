#include "MonitorHook.h"

namespace mmm
{
	MonitorHook::MonitorHook( const std::string& id, luabind::object table, 
		luabind::object function, luabind::object argument, Type type )
		: Hook( id, table, function, argument ), type_( type )
	{

	}
	
	MonitorHook::Type
	MonitorHook::getType() const
	{
		return type_;
	}

	void
	MonitorHook::setType( Type type )
	{
		type_ = type;
	}

	void 
	monitorhook_register( lua_State* state )
	{
		using namespace luabind;
		module(state)
		[
			class_<MonitorHook, Hook, HookPtr>( "MonitorHook" )
				.property( "hookType", &MonitorHook::getType, &MonitorHook::setType )				
				.scope
				[
					class_<MonitorHook::Type>("Type")
						.enum_("constants")
						[
							value("OnTrue", MonitorHook::OnTrue),
							value("OnFalse", MonitorHook::OnFalse),
							value("WhileTrue", MonitorHook::WhileTrue),
							value("WhileFalse", MonitorHook::WhileFalse),
							value("OnStop", MonitorHook::OnStop)
						]
				]
		];
	}

}
