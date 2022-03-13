#include "TextInputHook.h"

namespace mmm
{
	TextInputHook::TextInputHook( const std::string& id, luabind::object table,
		luabind::object function, luabind::object argument, const std::string& pattern )
		: Hook( id, table, function, argument ), pattern_( pattern )
	{

	}

	const std::string&
	TextInputHook::getPattern() const
	{
		return pattern_;
	}

	void
	TextInputHook::setPattern( const std::string& pattern )
	{
		pattern_ = pattern;
	}

	void
	textinputhook_register( lua_State* state )
	{
		using namespace luabind;
		module(state)
		[
			class_<TextInputHook, Hook, HookPtr>( "TextInputHook" )
				.property( "pattern", &TextInputHook::getPattern, &TextInputHook::setPattern )
		];
	}
}
