#pragma once

namespace mmm
{
	/**
		Base call for all hooks. Hosts common functionality
		for Hooks, such as identifiers and the like.
	*/
	class Hook
	{
	public:
		/**
			Get the id of the hook.
			@return The id.
		*/
		const std::string& getId( ) const;
		/**
			Get the current argument for the hook.
			@return The current argument.
		*/
		luabind::object getArgument( ) const;
		/**
			Get the table for the hook call.
			@return The current table.
		*/
		luabind::object getTable( ) const;
		/**
			Get the function for the hook call.
			@return The current function.
		*/
		luabind::object getFunction( ) const;
		/**
			Set the argument for the hook.
			@param argument The argument to use.
		*/
		void			setArgument( luabind::object argument );
		/**
			Call the hook function.
		*/
		template < typename ReturnType >
		void			call( );
	protected:
		/**
			Create a new hook with the specified identifier.
			@param id The identifier for the new hook.
		*/
		explicit Hook( const std::string& id, luabind::object table, 
			luabind::object function, luabind::object argument );
	private:
		std::string		id_;
		luabind::object table_;
		luabind::object function_;
		luabind::object argument_;
	};

	void hook_register( lua_State* state );
}
