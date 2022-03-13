#include "Application.h"
#include "ScriptErrors.h"

namespace mmm
{
	namespace
	{
		struct MMMApp
		{

		};
		luabind::object appRef;
		bool			cineractive;

		void application_cineractiveUpdate()
		{
			if( appRef.is_valid() )
			{
				try
				{
					luabind::object function = appRef["cineractiveUpdate"];
					if( function && luabind::type(function) == LUA_TFUNCTION )
					{
						luabind::call_function<void>( function, appRef );
					}
				}
				catch( const luabind::error& )
				{
					scriptError( std::string("Error in cineractiveUpdate : ") + 
									lua_tostring(common::Storage::instance().mainLuaVM, -1 ) );
				}
			}
		}
	}

	bool 
	application_isCineractive()
	{
		return cineractive;
	}

	void 
	application_setup( )
	{
		if( appRef.is_valid() )
		{
			try
			{
				luabind::object function = appRef["setup"];
				if( function && luabind::type(function) == LUA_TFUNCTION )
				{
					luabind::call_function<void>( function, appRef );
				}
			}
			catch( const luabind::error& )
			{
				scriptError( std::string( "Error in setup : ") + 
								lua_tostring( common::Storage::instance().mainLuaVM, -1  ) );
			}
		}
	}

	void 
	application_update( )
	{
		if( common::Storage::instance().error )
		{
			return;
		}

		if( cineractive )
		{
			application_cineractiveUpdate();
		}
		else if( appRef.is_valid( ) )
		{
			try
			{
				luabind::object function = appRef["update"];
				if( function && luabind::type(function) == LUA_TFUNCTION )
				{
					luabind::call_function<void>( function, appRef );
				}
			}
			catch( const luabind::error& )
			{
				scriptError( std::string("Error in update : ") + 
								lua_tostring(common::Storage::instance().mainLuaVM, -1 ) );
			}
		}
	}

	void
	application_resume( )
	{
		if( appRef.is_valid() )
		{
			try
			{
				luabind::object function = appRef["resume"];
				if( function && luabind::type(function) == LUA_TFUNCTION )
				{
					luabind::call_function<void>( function, appRef );
				}
			}
			catch( const luabind::error& )
			{
				scriptError( std::string("Error in resume : ") + 
								lua_tostring(common::Storage::instance().mainLuaVM, -1 ) );
			}
		}
	}

	void 
	application_cineractiveBegin( )
	{
		cineractive = true;
		if( appRef.is_valid() )
		{
			try
			{
				luabind::object function = appRef["cineractiveBegin"];
				if( function && luabind::type(function) == LUA_TFUNCTION )
				{
					luabind::call_function<void>( function, appRef );
				}
			}
			catch( const luabind::error& )
			{
				scriptError( std::string("Error in cineractiveBegin : ") + 
								lua_tostring(common::Storage::instance().mainLuaVM, -1 ) );
			}
		}
	}

	void 
	application_cineractiveFinish( bool forced )
	{
		if( appRef.is_valid() )
		{
			try
			{
				luabind::object function = appRef["cineractiveFinish"];
				if( function && luabind::type(function) == LUA_TFUNCTION )
				{
					luabind::call_function<void>( function, appRef, forced );
				}
			}
			catch( const luabind::error& )
			{
				scriptError( std::string("Error in cineractiveFinish : ") + 
								lua_tostring(common::Storage::instance().mainLuaVM, -1 ) );
			}
		}
		cineractive = false;
	}

	void
	application_appRegister( luabind::object object )
	{
		appRef = object;
	}

	void
	application_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<MMMApp>("MMM")
				.scope
				[
					def("register", &application_appRegister )
				]
		];
	}
}
