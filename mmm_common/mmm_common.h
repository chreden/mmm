#ifndef _MMM_MMMCOMMON_H
#define _MMM_MMMCOMMON_H

#include "Externals.h"

#include "Hash.h"
#include "FilePath.h"
#include "ModFolder.h"

//I hate to do it, but these defines have to go somewhere....
#define _FLEETOPS
#ifdef _FLEETOPS
	#define _FLEETOPS_VERSION 3150
#endif

struct lua_State;

//Some sort of repository for variables and the like
namespace mmm
{
	class DebuggerConnection;
	typedef std::shared_ptr<DebuggerConnection> DebuggerConnectionPtr;

	namespace common
	{
		class Storage
		{
		public:
			Storage( );
			bool			error;				//Has there been an error?
			float			updateTime;			//Interval desired between updates
			
			luapack::Pack	missionPack;		//Mission pack loaded.
			FilePath		path;

			bool			fleetops;

			ModFolder		modFolder;

			lua_State*		mainLuaVM;			//Main Lua VM.
			static Storage& instance( );
		};


		//String manip.
		template<typename T>
		std::string typeToString( const T& value )
		{
			std::stringstream stream;
			stream << value;
			return value.str();
		}
	}
}

#endif
