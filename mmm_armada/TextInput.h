#pragma once

namespace mmm
{
	class TextInput
	{
	public:
		/**
			Hook the chat input so that the specified function is called when any
			text is entered.
			@param id The id for the new hook.
			@param table The lua table to use as self.
			@param function The lua function to call.
			@param arg The argument to pass to the callback.
		*/
		bool hook( const std::string& id, luabind::object table, luabind::object function, luabind::object argument );
		/**
			Hook the chat input so that the specified function is called when the
			text entered matches the given pattern.
			@param id The id for the new hook.
			@param table The lua table to use as self.
			@param function The lua function to call.
			@param argument The argument to pass to the callback.
			@param pattern The regex to use as a filter.
		*/
		bool hook( const std::string& id, luabind::object table, luabind::object function, luabind::object argument, const std::string& pattern );

		/**
			Remove a hook from TextInput.
		*/
		bool unhook( const std::string& id );

		bool unhook( HookPtr hook );
		/**
			Query if the player is entering text into the chat box.
			@return True if the chat is active.
		*/
		bool getActive() const;
		/**
			Get the prompt shown on the chat box.
			@return The text shown before the :.
		*/
		const std::string getPrompt( ) const;
		/**
			Get the currently entered text.
			@return The current value of the chat box.
		*/
		const std::string getText( ) const;

		luabind::object getHooks( ) const;

		/**
			Set the prompt before the chat text.
			@param prompt The prompt to show.
		*/
		void setPrompt( const std::string& prompt );

		void update( );
	private:
		std::unordered_map<std::string, TextInputHookPtr> hooks_;
		bool		previousActive_;
		std::string	previousString_;
	};

	void textinput_update( );
	void textinput_register( lua_State* state );
}
