#include "TextInput.h"
#include "ScriptErrors.h"
#include "TextInputHook.h"

namespace mmm
{
	namespace 
	{
		TextInput textInput;
		const std::size_t Address_IsActive = 0x0065f120;
		const std::size_t Address_GetString = 0x0065e860;
		const std::size_t Address_SetPrompt = 0x0065e730;
	}

	void 
	TextInput::update( )
	{
		common::Storage& storage( common::Storage::instance( ) );
		lua_State* state = storage.mainLuaVM;

		void* context = memory_function< void* (*)() >( Address_IsActive )( );
		//Check to see if anything has changed.
		bool active = context != 0;

		if( active )
		{
			//Capture string here.
			previousString_ = memory_function< char* (*)(void*) >( Address_GetString )( context );
		}
		else if( active != previousActive_ )
		{
			//Used with pattern matching hooks.
			luabind::object findFunction;
			luabind::object stringObject = luabind::globals(common::Storage::instance().mainLuaVM)["string"];
			if( stringObject.is_valid() )
			{
				findFunction = stringObject["find"];
			}

			auto hookCopy = hooks_;
			for( auto iter = hookCopy.begin();
				 iter != hookCopy.end();
				 ++iter )
			{
				try
				{
					TextInputHookPtr hook = iter->second;

					if( !hook->getPattern().empty() && findFunction.is_valid() )
					{
						//The hook has a pattern that needs to be matched -
						//if it passes then we will use it, otherwise we just
						//bail out.
						luabind::object found = luabind::call_function<luabind::object>( findFunction, previousString_, hook->getPattern() );
						if( luabind::type(found) == LUA_TNIL ) 
						{
							continue;
						}
					}

					if( hook->getTable().is_valid() && 
						luabind::type( hook->getTable() ) != LUA_TNIL )
					{
						luabind::call_function<void>( hook->getFunction(), hook->getTable(), previousString_, hook );
					}
					else
					{
						luabind::call_function<void>( hook->getFunction(), previousString_, hook );
					}
				}
				catch( const luabind::error& )
				{
					scriptError( std::string("Error in TextInput hook (" + iter->first + "): ") + lua_tostring( state, -1 ) );
				}
			}
		}

		previousActive_ = active;
	}

	bool 
	TextInput::getActive() const
	{
		return memory_function< void* (*)() >( Address_IsActive )( ) != nullptr;
	}

	const std::string 
	TextInput::getPrompt( ) const
	{
		return "";
	}

	const std::string 
	TextInput::getText( ) const
	{
		void* context = memory_function< void* (*)() >( Address_IsActive )( );
		if( context )
		{
			return memory_function< char* (*)(void*) >( Address_GetString )( context );
		}
		return "";
	}

	void
	TextInput::setPrompt( const std::string& prompt )
	{
		void* context = memory_function< void* (*)() >( Address_IsActive )( );
		if( context )
		{
			memory_function< void (*)(void*,char*) >( Address_SetPrompt 
				)( context, const_cast<char*>( prompt.c_str( ) ) );
		}
	}

	bool
	TextInput::hook( const std::string& id, luabind::object table, luabind::object function, luabind::object argument )
	{
		return hook( id, table, function, argument, "" );
	}

	bool
	TextInput::hook( const std::string& id, luabind::object table, luabind::object function, luabind::object argument, const std::string& pattern )
	{
		if( hooks_.find( id ) != hooks_.end() )
		{
			return false;
		}
		hooks_[id] = TextInputHookPtr( new TextInputHook( id, table, function, argument, pattern ) );
		return true;
	}

	bool
	TextInput::unhook( const std::string& id )
	{
		auto iter = hooks_.find( id );
		if( iter != hooks_.end() )
		{
			hooks_.erase( iter );
			return true;
		}
		return false;
	}

	bool
	TextInput::unhook( HookPtr hook )
	{
		if( !hook )
		{
			return false;
		}
		
		auto iter = hooks_.find( hook->getId() );
		if( iter == hooks_.end() )
		{
			return false;
		}

		hooks_.erase( iter );
		return true;
	}

	luabind::object
	TextInput::getHooks( ) const
	{
		luabind::object results = luabind::newtable(common::Storage::instance().mainLuaVM);
		for( auto iter = hooks_.begin(); iter != hooks_.end(); ++iter )
		{
			results[iter->first] = HookPtr( iter->second );
		}	
		return results;
	}

	void
	textinput_update( )
	{
		textInput.update();
	}

	void
	textinput_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<TextInput>("TextInput_")
				.property( "prompt", &TextInput::getPrompt, &TextInput::setPrompt )
				.property( "text", &TextInput::getText )
				.property( "active", &TextInput::getActive )
				.property( "hooks", &TextInput::getHooks )
				.def( "hook", (bool (TextInput::*)(const std::string&, luabind::object, luabind::object, luabind::object))&TextInput::hook )
				.def( "hook", (bool (TextInput::*)(const std::string&, luabind::object, luabind::object, luabind::object, const std::string&))&TextInput::hook )
				.def( "unhook", (bool (TextInput::*)(const std::string&))&TextInput::unhook)
				.def( "unhook", (bool (TextInput::*)(HookPtr))&TextInput::unhook)
		];

		globals(state)["TextInput"] = &textInput;
	}
}