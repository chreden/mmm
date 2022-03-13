#include "EntityHook.h"

namespace mmm
{
	EntityHook::EntityHook( const std::string& id, Type type, luabind::object table, 
		luabind::object function, luabind::object argument )
		: Hook( id, table, function, argument ), type_( type )
	{

	}

	EntityHook::Type
	EntityHook::getType() const
	{
		return type_;
	}

	void
	EntityHook::setType( Type type )
	{
		type_ = type;
	}

	void
	entityhook_register( lua_State* state )
	{
		using namespace luabind;
		module(state)
		[
			class_<EntityHook, Hook, HookPtr>( "EntityHook" )
				.property( "hookType", &EntityHook::getType, &EntityHook::setType )
				.scope
				[
					class_<EntityHook::Type>("Type")
						.enum_("constants")
						[
							value("OnDestroy", EntityHook::OnDestroy ),
							value("OnReplace", EntityHook::OnReplace )
						]
				]
		];
	}
}

