#pragma once

#include "Hook.h"

namespace mmm
{
	/**
		Hooks for TextInput.
	*/
	class TextInputHook : public Hook
	{
	public:
		/**
			Create a new TextInputHook.
			@param id The id for the new hook.
			@param table The table for the hook function.
			@param function The function to call.
			@param argument The argument to store in the hook.
			@param pattern The Lua pattern to use to filter text input.
		*/
		explicit TextInputHook( const std::string& id, luabind::object table,
			luabind::object function, luabind::object argument, const std::string& pattern );
		/**
			Get the pattern used for this hook.
			@return The Lua pattern used.
		*/
		const std::string& getPattern() const;
		/**
			Set the new pattern for the hook.
			@param pattern The new Lua pattern to use.
		*/
		void setPattern( const std::string& pattern );
	private:
		std::string pattern_;
	};

	void textinputhook_register( lua_State* state );
}
