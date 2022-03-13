#include "Hook.h"

namespace mmm
{
	Hook::Hook( const std::string& id, luabind::object table, 
		luabind::object function, luabind::object argument  )
		: id_( id ), table_( table ), function_( function), argument_( argument )
	{

	}

	const std::string&
	Hook::getId( ) const
	{
		return id_;
	}

	luabind::object 
	Hook::getArgument( ) const
	{
		return argument_;
	}

	luabind::object
	Hook::getTable( ) const
	{
		return table_;
	}

	luabind::object
	Hook::getFunction( ) const
	{
		return function_;
	}

	void
	Hook::setArgument( luabind::object argument )
	{
		argument_ = argument;
	}

	void 
	hook_register( lua_State* state )
	{
		using namespace luabind;
		module(state)
		[
			class_<Hook, HookPtr>( "Hook" )
				.property( "id", &Hook::getId )
				.property( "argument", &Hook::getArgument, &Hook::setArgument )
		];
	}
}
