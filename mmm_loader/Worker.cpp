#include "Worker.h"
//Including the parts of armada we actually need to use.
#include "../mmm_armada/Cineractive_Internal.h"
#include "../mmm_armada/Game_Internal.h"
#include "../mmm_armada/UI_Internal.h"
#include "../mmm_armada/ScriptInterface.h"
#include "../mmm_armada/Debug_Internal.h"
#include "../mmm_armada/Media_Internal.h"
#include "../mmm_armada/Game_Internal.h"
#include "../mmm_armada/Entities_Internal.h"
#include "../mmm_armada/Nebula_Internal.h"
#include "../mmm_armada/Type_Nebula.h"

namespace mmm
{
	Worker* Worker::instance;

	namespace
	{
		float lastUpdate_;

		void workerUpdate( )
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

		void setupLua()
		{
			initLua();
			std::string maptitle = Game().getMapTitle();

			try
			{
				//Try and get the pack file that we have found.
				common::Storage& storage = common::Storage::instance();
				std::string packFilePath;
				if (storage.modFolder.getFile(maptitle + ".mmmpack", packFilePath))
				{
					storage.missionPack.load(packFilePath.c_str());
				}
			}
			catch (...)
			{
				//Doesn't really matter as we will just attempt to load the script file
				//from the file instead.
			}

			globals_include(maptitle + ".lua");
		}

		constexpr std::size_t Transport_IsInstantAction = 0x005576F0;

		/// <summary>
		/// If Fleetops is present change the Transport::IsInstantAction function to return 1 at all times as it doesn't seem to work when only single player is set.
		/// </summary>
		void enableSaveButtons()
		{
			if (common::fleetops_present())
			{
				DWORD old_protect = 0;
				uint8_t* instruction = reinterpret_cast<uint8_t*>(Transport_IsInstantAction);
				VirtualProtect(instruction, 2, PAGE_READWRITE, &old_protect);
				instruction[0] = 0xb0;
				instruction[1] = 0x01;
				VirtualProtect(instruction, 2, old_protect, &old_protect);
			}
		}

		/// <summary>
		/// Sets the Transport::IsInstantAction function back to the way it was before the loader was loaded.
		/// </summary>
		void restoreSaveButtons()
		{
			if (common::fleetops_present())
			{
				DWORD old_protect = 0;
				uint8_t* instruction = reinterpret_cast<uint8_t*>(Transport_IsInstantAction);
				VirtualProtect(instruction, 2, PAGE_READWRITE, &old_protect);
				instruction[0] = 0x32;
				instruction[1] = 0xc0;
				VirtualProtect(instruction, 2, old_protect, &old_protect);
			}
		}

		/// <summary>
		/// Stop all nebula rotation by default as they already rotate in animation - this
		/// extra rotation makes them go too fast.
		/// </summary>
		void stopNebulas()
		{
			const EntityPointerManager* const epm = GetEntityPointerManager();
			for (int i = 0; i < EntityPointerManager::MaxEntities; ++i)
			{
				const EntityPointer& entity = epm->m_entity_pointer[i];
				if (entity.m_id.m_used && types::isNebula(entity.m_entity))
				{
					auto nebula = static_cast<types::Nebula*>(entity.m_entity);
					nebula->delta_yaw = 0.0f;
					nebula->delta_pitch = 0.0f;
					nebula->delta_roll = 0.0f;
				}
			}
		}
	}

	Worker::Worker( )
	:  inputControlsSet_( false ), workerRule_( "Worker" )
	{
		lastUpdate_ = 0;
		instance = this;

		enableSaveButtons();
		stopNebulas();
	}

	Worker::~Worker( )
	{
		//Have to unhook ourself.
		auto script_interface = getScriptInterface();
		if (script_interface)
		{
			script_interface->MonitorInputControls(0);
		}
		
		shutdownLua( );
		FreeConsole( );

		Debug().disconnect();

		//Clears the IEEE of all rules (Trash all rules)
		memory_function<void (*)()>( 0x004067c0 )();
		restoreSaveButtons();
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