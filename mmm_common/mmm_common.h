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

			ModFolder		modFolder;

			lua_State*		mainLuaVM;			//Main Lua VM.
			static Storage& instance( );
		};

		struct Version
		{
			int major{ 0 };
			int minor{ 0 };
			int patch{ 0 };
			int revision{ 0 };
		};

		/// <summary>
		/// Whether the loader is in a Fleetops game.
		/// </summary>
		bool fleetops_present() noexcept;

		/// <summary>
		/// Get the version of Fleetops present.
		/// </summary>
		Version fleetops_version() noexcept;
	}
}

#endif
