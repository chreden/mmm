#pragma once

#include "Hook.h"

namespace mmm
{
	class EntityHook : public Hook
	{
	public:
		enum Type
		{
			OnDestroy,
			OnReplace
		};

		/**
			Create a new EntityHook.
			@param id The id for the new hook.
			@param table The table for the hook function.
			@param function The function to call.
			@param argument The argument to store in the hook.
			@param type The Entity hook type
		*/
		explicit EntityHook( const std::string& id, Type type, luabind::object table,
			luabind::object function, luabind::object argument );

		Type getType() const;

		void setType( Type type );

	private:
		Type type_;
	};

	void entityhook_register( lua_State* state );
}
