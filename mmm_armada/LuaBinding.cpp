#include "LuaBinding.h"	

#include "Globals.h"
#include "Application.h"
#include "Timer.h"

#include "Test.h"
#include "Container.h"

#include "MonitorWrapper.h"

#include "Explosion_Internal.h"
#include "ConstructionObject_Internal.h"
#include "CraftSystem_Internal.h"
#include "Freighter_Internal.h"
#include "RepairShip_Internal.h"
#include "Colony_Internal.h"
#include "Evolver_Internal.h"
#include "ConstructionRig_Internal.h"
#include "AsteroidField.h"
#include "Scavenger.h"
#include "PlanetMiningBase.h"
#include "SensorArray.h"
#include "BuildQueue.h"

#include "Objective.h"

	#include "MiningStation.h"
	#include "Planet_Internal.h"
	#include "ResourceTransferInterface.h"
		#include "Starbase_Internal.h"

	#include "BackgroundObject_Internal.h"
	#include "UtritiumBall_Internal.h"
	#include "Scrap_Internal.h"
		#include "IonStorm_Internal.h"
		#include "Nebula_Internal.h"
		#include "Wormhole.h"
		#include "BlackHole_Internal.h"	
		#include "LatinumNebula_Internal.h"

	#include "PulsePhaser_Internal.h"
	#include "Artillery.h"
	#include "Phaser_Internal.h"
	#include "PhotonTorpedo_Internal.h"
	#include "BeamToggle.h"
#include "AntimatterMine.h"
#include "GravityMine.h"

#include "OrdnanceDamage.h"

#include "ResourceInterface_Internal.h"

#include "Mission_Internal.h"
#include "Team_Internal.h"
#include "Race_Internal.h"
#include "Game_Internal.h"
#include "Entities_Internal.h"
#include "Path_Internal.h"
#include "Cineractive_Internal.h"
#include "Load_Internal.h"
#include "Save_Internal.h"
#include "Debug_Internal.h"
#include "UI_Internal.h"
#include "TextInput.h"
#include "Media_Internal.h"
#include "Camera_Internal.h"
#include "Map_Internal.h"
#include "EntityFinder.h"
#include "Monitor.h"
#include "Objectives_Internal.h"
#include "Matrix.h"
#include "ResearchPod_Internal.h"
#include "ResearchStation.h"
#include "CargoShip_Internal.h"
#include "TradingStation.h"
#include "Type_TradingStation.h"

#include "GameObjectClass_Internal.h"
	#include "CraftClass_Internal.h"
		#include "ColonyClass_Internal.h"
		#include "RepairShipClass_Internal.h"
		#include "ProducerClass_Internal.h"
			#include "MiningStationClass_Internal.h"
				#include "TradingStationClass_Internal.h"
			#include "EvolverClass_Internal.h"
	#include "TerrainObjectClass_Internal.h"
		#include "LatinumNebulaClass_Internal.h"
		#include "AreaEffectObjectClass_Internal.h"
			#include "BlackHoleClass_Internal.h"
			#include "UtritiumBallClass_Internal.h"
		#include "ScrapClass_Internal.h"
		#include "BackgroundObjectClass_Internal.h"
			
#include "OrientedQueue.h"

#include "Hook.h"
	#include "TextInputHook.h"
	#include "TimerHook.h"
	#include "MonitorHook.h"
	#include "EntityHook.h"


namespace mmm
{
	void 
	initLua( )
	{
		lua_State* state = lua_open( );
		common::Storage::instance().mainLuaVM = state;
		
		//File library disabled as well as os.
		static const luaL_Reg lualibs[] = 
		{
		  {"", luaopen_base},
		  {LUA_LOADLIBNAME, luaopen_package},
		  {LUA_TABLIBNAME, luaopen_table},
		  {LUA_STRLIBNAME, luaopen_string},
		  {LUA_MATHLIBNAME, luaopen_math},
		  {LUA_DBLIBNAME, luaopen_debug},
		  {0, 0}
		};

		const luaL_Reg *lib = lualibs;
		for (; lib->func; lib++) 
		{
			lua_pushcfunction(state, lib->func);
			lua_pushstring(state, lib->name);
			lua_call(state, 1, 0);
		}

		luabind::open( state );

		registerTypes( );
	}

	void 
	shutdownLua( )
	{
		lua_State* state = common::Storage::instance( ).mainLuaVM;
		if (state)
		{
			lua_close(state);
		}
		common::Storage::instance( ).mainLuaVM = 0;
	}

	void
	registerTypes( )
	{
		lua_State* state = common::Storage::instance( ).mainLuaVM;

		globals_register( state );
		application_register( state );
		timer_register( state );
		
		craftsystem_register( state );
		ordnancedamage_register( state );

		matrix_register( state );
		objective_register( state );

		container_register( state );

		test_register( state );

		hook_register( state );
			textinputhook_register( state );
			timerhook_register( state );
			monitorhook_register( state );
			entityhook_register( state );

		buildqueue_register( state );

		queue_register( state );
			splinequeue_register( state );
				orientedqueue_register( state );

		gameobjectclass_register( state );
			craftclass_register( state );
				colonyclass_register( state );
				producerclass_register( state );
					miningstationclass_register( state );
						tradingstationclass_register( state );
					evolverclass_register( state );
				repairshipclass_register( state );
			terrainobjectclass_register( state );
				scrapclass_register( state );
				backgroundobjectclass_register( state );
				latinumnebulaclass_register( state );
				areaeffectobjectclass_register( state );
					blackholeclass_register( state );
					utritiumballclass_register( state );

		entity_register( state );
			
			resourceinterface_register( state );
			gameobject_register( state );
				constructionobject_register( state );
				craft_register( state );
					cargoship_register( state );
					freighter_register( state );	
					repairship_register( state );
					colony_register( state );
					scavenger_register( state );
					researchpod_register( state );
					sensorarray_register( state );
					planetminingbase_register( state );
					producer_register( state );
						planet_register( state );
						evolver_register( state );
						constructionrig_register( state );
						resourcetransferinterface_register( state );
						researchstation_register( state );
							miningstation_register( state );
								tradingstation_register( state );
						shipyard_register( state );
							starbase_register( state );
				terrainobject_register( state );
					asteroidfield_register( state );
					scrap_register( state );
					utritiumball_register( state );
					backgroundobject_register( state );
					latinumnebula_register( state );
					areaeffectobject_register( state );	
						wormhole_register( state );
						nebula_register( state );
						ionstorm_register( state );
						blackhole_register( state );
			explosion_register( state );
			ordnance_register( state );
				beam_register( state );
					phaser_register( state );
				beamtoggle_register( state );
				missile_register( state );
					photontorpedo_register( state );
				bullet_register( state );
					artillery_register( state );
					pulsephaser_register( state );
				mine_register( state );
					gravitymine_register( state );
					antimattermine_register( state );

		vector_register( state );
		mission_register( state );
		team_register( state );
		race_register( state );
		game_register( state );
			
		path_register( state );
		cineractive_register( state );
		load_register( state );
		save_register( state );
		debug_register( state );
		ui_register( state );
		textinput_register( state );	
		media_register( state );
		camera_register( state );
		map_register( state );
		entityfinder_register( state );
		monitor_register( state );

		objectives_register( state );

		colour_register( state );
	}
}