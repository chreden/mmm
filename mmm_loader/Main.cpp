#include "Worker.h"

#include "../mmm_armada/ScriptInterface.h"
#include "../mmm_armada/Types.h"
#include "../mmm_armada/Game_Internal.h"
#include <Windows.h>

namespace mmm
{
	//The worker used for our dll.
	Worker worker;

	bool firstUpdate = true;
	bool isANewGame = false;
	
	unsigned char ccon InputHandler( ) 
	{
		//Special part for the first update - some things cause crashes
		//if they are called at the wrong time ( such as the objectives being
		//set ). The wrong time being during script init or script extend
		//interface.
		if( firstUpdate )
		{
			if( isANewGame )
			{
				worker.Startup( );
			}
			else
			{
				worker.Resume( );
			}

			firstUpdate = false;
		}

		//Returning 0 breaks it, so 1 it is. At some point I'll have to find
		//out what this is supposed to do. Could be an bool.
		return 1;
	}

	//Need this for the rule reload fix. 
	int loaderFunction( )
	{
		getScriptInterface( )->MonitorInputControls( InputHandler );
		return 0;
	}

	//Need this for the second parameter to the rule reload fix.
	void loaderStub( ) { }

	//Sets up the rules fix that gives us access on the same thread.
	void SetupReload( ScriptInterface* param )
	{
		const std::size_t Address_WorldCharacter = 0x007349c8;

		const std::size_t Function_GetIIIE				 = 0x00403250;
		const std::size_t Function_CreateRule			 = 0x00405fd0;
		const std::size_t Function_AddDependentRule		 = 0x004055e0;
		const std::size_t Function_AddRuleToAffectedList = 0x00405a00;
		
		typedef int (*fun1)();
		typedef void (*fun2)();

		character* world = reinterpret_cast<character*>( Address_WorldCharacter );

		IIIE& iiie = (world->*memory_function<IIIE& (character::*)()>(Function_GetIIIE))();

		rule* reloader = (iiie.*memory_function<rule* (IIIE::*)(fun1, fun2, const char*)>(Function_CreateRule))(loaderFunction, loaderStub, "reloader");

		//No reason for hot int, just needed any kind of hot type.
		hot_int* hotint = param->ScriptCreate_hot_int( "loadHot" );

		(hotint->*memory_function<void (hot_int::*)(rule*)>(Function_AddDependentRule))(reloader);

		(iiie.*memory_function<void (IIIE::*)(rule*)>(Function_AddRuleToAffectedList))(reloader);
	}

	/// <summary>
	/// This is called by A2 when it loads the DLL.
	/// </summary>
	/// <param name="param">Script interface passed by the game.</param>
	extern "C" int ScriptExtendInterface( ScriptInterface* param ) 
	{
		bool editMode = *(*reinterpret_cast<bool**>( 0x0076B5AC ) + 0x84);

		if( editMode )
		{
			return 51;
		}

		SetupReload( param );

		mmm::setScriptInterface( param );

		//Apparently this is the minimum version they want. It complains
		//if you give a lower version.
		return 51;
	}

	//This is only called by Armada when the game is loaded for the first time.
	//It does not get called when you load a savegame. If this function is called, 
	//we can tell that this is not a savegame.
	extern "C" int ScriptInit( void* ) 
	{
		bool editMode = *(*reinterpret_cast<bool**>( 0x0076B5AC ) + 0x84);

		if( editMode )
		{
			return 51;
		}

		ScriptInterface* scriptInterface = getScriptInterface( );

		scriptInterface->MonitorInputControls( InputHandler );

		isANewGame = true;

		return 0;
	}

	extern "C" __declspec(dllexport) BOOL WINAPI DllMain(
		HINSTANCE hinstDLL,  // handle to DLL module
		DWORD fdwReason,     // reason for calling function
		LPVOID lpvReserved)  // reserved
	{
		// Perform actions based on the reason for calling.
		switch (fdwReason)
		{
		case DLL_PROCESS_ATTACH:
			// Initialize once for each new process.
			// Return FALSE to fail DLL load.
			break;

		case DLL_THREAD_ATTACH:
			// Do thread-specific initialization.
			break;

		case DLL_THREAD_DETACH:
			// Do thread-specific cleanup.
			break;

		case DLL_PROCESS_DETACH:

			if (lpvReserved != nullptr)
			{
				break; // do not do cleanup if process termination scenario
			}

			worker.Shutdown();
			break;
		}
		return TRUE;  // Successful DLL_PROCESS_ATTACH.
	}
}