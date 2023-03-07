#include "Globals.h"
#include "PrintMessages.h"
#include "ScriptErrors.h"
#include "Debug_Internal.h"

namespace mmm
{
	void 
	globals_include( const std::string& fn )
	{
		common::Storage& storage = common::Storage::instance();
	
		common::FilePath oldPath = storage.path;
		try
		{
			std::string filename = storage.path.goTo( fn );
			
			lua_State* state = storage.mainLuaVM;
			luapack::FilePtr file = pack_getFile( storage.missionPack, filename.c_str() );
			if( file )
			{
				if( luaL_dostring( state, file->getFileData() ) )
				{
					scriptError( std::string("Error in include : ") + lua_tostring(state, -1) );
				}
			}
			else
			{
				std::string finalFilePath;
				if( storage.modFolder.getFile( filename, finalFilePath ) )
				{
					if( luaL_dofile( state, finalFilePath.c_str( ) ) )
					{
						scriptError( std::string("Error in include : ") + lua_tostring( state, -1 ) );
					}
				}
			}
		}
		catch(int)
		{
			scriptError("Error : invalid include specified");
		}

		//Go back to directory we were in?
		storage.path = oldPath;
	}

	int globals_print2(lua_State* L)
	{
		print::add(lua_tostring(L, -1));
		return 0;
	}

	void globals_register(lua_State* state)
	{
		using namespace luabind;
		module(state)
		[
			def( "include", &globals_include ),
			def( "clearPrint", &print::clear )
		];

		lua_pushcfunction(state, globals_print2);
		lua_setglobal(state, "print");
	}
}