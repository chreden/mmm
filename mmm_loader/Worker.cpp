#include "Worker.h"
//Including the parts of armada we actually need to use.
#include "../mmm_armada/Cineractive_Internal.h"
#include "../mmm_armada/Game_Internal.h"
#include "../mmm_armada/UI_Internal.h"
#include "../mmm_armada/ScriptInterface.h"
#include "../mmm_armada/Debug_Internal.h"
#include "../mmm_armada/Media_Internal.h"
#include "../mmm_armada/Game_Internal.h"

namespace mmm
{
	Worker* Worker::instance;

	namespace
	{
		float lastUpdate_;

		void
		workerUpdate( )
		{
			common::Storage& storage = common::Storage::instance();

			if( !storage.error && 
				 Game().getTime( ) - lastUpdate_ >= storage.updateTime )
			{
				EntityReference::updateReferences();
				timer_update( );
				UI().update( );
				textinput_update( );
				Monitor::update( );
				Media::update( );
			
				application_update( );

				if( DebuggerConnection::getInstance().connected() )
				{
					DebuggerConnection::getInstance().update();
				}

				lastUpdate_ = Game().getTime( );
			}

			if( application_isCineractive() &&
				GetAsyncKeyState( VK_SPACE ) &&
				Cineractive().isSkippable() &&
				GetForegroundWindow() == Game().getWindow() )
			{
				Cineractive().forceEnd( );
			}
		}
	}

	Worker::Worker( )
	:  inputControlsSet_( false ), workerRule_( "Worker" )
	{
		lastUpdate_ = 0;
		instance = this;
	}

	Worker::~Worker( )
	{
		//Have to unhook ourself.
		getScriptInterface( )->MonitorInputControls( 0 );
		shutdownLua( );
		FreeConsole( );

		Debug().disconnect();

		//Clears the IEEE of all rules (Trash all rules)
		memory_function<void (*)()>( 0x004067c0 )();
	}

	namespace
	{
		void
		setupLua()
		{
			initLua( );
			std::string maptitle = Game().getMapTitle( );
			
			try
			{
				//Try and get the pack file that we have found.
				common::Storage& storage = common::Storage::instance();
				std::string packFilePath;
				if( storage.modFolder.getFile( maptitle + ".mmmpack", packFilePath ) )
				{
					storage.missionPack.load( packFilePath.c_str() );
				}
			}
			catch(...)
			{
				//Doesn't really matter as we will just attempt to load the script file
				//from the file instead.
			}

			globals_include( maptitle + ".lua" );
		}
	}

	void Worker::Startup( )
	{
		setupLua();
		if( !common::Storage::instance( ).error )
		{
			application_setup( );
		}
		workerRule_.activate( workerUpdate );
	}
	
	void Worker::Resume( )
	{
		setupLua();
		if( !common::Storage::instance( ).error )
		{
			application_resume( );
		}
		workerRule_.activate( workerUpdate );
	}
}