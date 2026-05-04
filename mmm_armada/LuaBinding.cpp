#include "LuaBinding.h"	

#include "Globals.h"
#include "Application.h"
#include "Team_Internal.h"
#include "EntityFinder.h"
#include "Entity_Internal.h"
#include "Vector3.h"
#include "Cineractive_Internal.h"
#include "UI_Internal.h"
#include "Media_Internal.h"
#include "Race_Internal.h"
#include "Timer.h"
#include "GameObject_Internal.h"
#include "Path_Internal.h"
#include "Objectives_Internal.h"
#include "Objective.h"
#include "GameObjectClass_Internal.h"
#include "Craft_Internal.h"
#include "TradingStation.h"
#include "BuildQueue.h"
#include "Planet_Internal.h"
#include "OrientedQueue.h"
#include "Game_Internal.h"
#include "Camera_Internal.h"
#include "MineArray.h"
#include "Mine.h"
#include "Debug_Internal.h"
#include "OrdnanceDamage.h"
#include "Mission_Internal.h"
#include "Map_Internal.h"
#include "IonStorm_Internal.h"
#include "Load_Internal.h"
#include "Save_Internal.h"
#include "Wormhole.h"
#include "Test.h"
#include "Matrix.h"
#include "TextInput.h"
#include "Monitor.h"
#include "MonitorHook.h"

/*
*
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
#include "SensorArray.h"


#include "Objective.h"

    #include "MiningStation.h"
    
    #include "ResourceTransferInterface.h"
        #include "Starbase_Internal.h"

    #include "BackgroundObject_Internal.h"
    #include "Scrap_Internal.h"
        #include "IonStorm_Internal.h"
        #include "Nebula_Internal.h"
        #include "Wormhole.h"
        #include "BlackHole_Internal.h"	
        #include "LatinumNebula_Internal.h"

    #include "PulsePhaser_Internal.h"
    #include "PhotonTorpedo_Internal.h"
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
#include "Objectives_Internal.h"
#include "Matrix.h"
#include "ResearchPod_Internal.h"
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
        #include "ScrapClass_Internal.h"
        #include "BackgroundObjectClass_Internal.h"
            
#include "OrientedQueue.h"

#include "Hook.h"
    #include "TextInputHook.h"
    #include "TimerHook.h"
    #include "MonitorHook.h"
    #include "EntityHook.h"
*/

namespace mmm
{
    void initLua()
    {
        lua_State* state = luaL_newstate();
        common::Storage::instance().mainLuaVM = state;
        
        static const luaL_Reg loadedlibs[] = {
          {LUA_GNAME, luaopen_base},
          {LUA_LOADLIBNAME, luaopen_package},
          {LUA_COLIBNAME, luaopen_coroutine},
          {LUA_TABLIBNAME, luaopen_table},
          {LUA_STRLIBNAME, luaopen_string},
          {LUA_MATHLIBNAME, luaopen_math},
          {LUA_UTF8LIBNAME, luaopen_utf8},
          {NULL, NULL}
        };

        const luaL_Reg* lib;
        /* "require" functions from 'loadedlibs' and set results to global table */
        for (lib = loadedlibs; lib->func; lib++) {
            luaL_requiref(state, lib->name, lib->func, 1);
            lua_pop(state, 1);  /* remove lib */
        }

        registerTypes();
    }

    void shutdownLua()
    {
        lua_State* state = common::Storage::instance().mainLuaVM;
        if (state)
        {
            lua_close(state);
        }
        common::Storage::instance().mainLuaVM = 0;
    }

    void registerTypes()
    {
        lua_State* state = common::Storage::instance().mainLuaVM;

        globals_register(state);
        application_register(state);
        team_register(state);
        entityfinder_register(state);
        monitor_register(state);

        hook_register(state);
        monitorhook_register(state);
        entityhook_register(state);

        vector_register(state);
        colour_register(state);
        cineractive_register(state);
        ui_register(state);
        media_register(state);
        race_register(state);
        timer_register(state);
        path_register(state);
        
        objectives_register(state);
        buildqueue_register(state);
        queue_register(state);
        game_register(state);
        camera_register(state);
        debug_register(state);
        mission_register(state);
        map_register(state);
        container_register(state);
        load_register(state);
        save_register(state);
        test_register(state);
        matrix_register(state);
        textinput_register(state);

        entity_register(state);
        gameobject_register(state);
                craft_register(state);
                    minearray_register(state);
                        planet_register(state);
                        // resourcetransferinterface_register(state);
                                tradingstation_register(state);
                    // scrap_register(state);
                    // utritiumball_register(state);
                        wormhole_register(state);
                        // nebula_register(state);
                        // ionstorm_register(state);
        mine_register(state);
        ionstorm_register(state);

        gameobjectclass_register(state);
        ordnancedamage_register(state);

        /*
        craftsystem_register(state);

        objective_register(state);

        hook_register(state);
            textinputhook_register(state);
            timerhook_register(state);

        entity_register(state);
            
                craft_register(state);
                        resourcetransferinterface_register(state);
                        researchstation_register(state);
                            miningstation_register(state);
                    scrap_register(state);
                        nebula_register(state);
                        ionstorm_register(state);
            explosion_register(state);
                bullet_register(state);
                    pulsephaser_register(state);

        mission_register(state);
            
        load_register(state);
        textinput_register(state);	
        
        */
    }

    void assign_metatable(lua_State* L, int ref_index)
    {
        lua_rawgeti(L, LUA_REGISTRYINDEX, ref_index);
        lua_setmetatable(L, -2);
    }

    void create_enum(lua_State* L, const std::string& name, const std::vector<std::tuple<std::string, int>>& values)
    {
        lua_newtable(L);
        for (const auto& v : values)
        {
            lua_pushinteger(L, std::get<1>(v));
            lua_setfield(L, -2, std::get<0>(v).c_str());
        }
        lua_setfield(L, -2, name.c_str());
    }

    void create_metatable(lua_State* L, lua_CFunction index, lua_CFunction newindex, lua_CFunction gc, lua_CFunction call)
    {
        lua_newtable(L);
        if (index)
        {
            lua_pushcfunction(L, index);
            lua_setfield(L, -2, "__index");
        }
        if (newindex)
        {
            lua_pushcfunction(L, newindex);
            lua_setfield(L, -2, "__newindex");
        }
        if (gc)
        {
            lua_pushcfunction(L, gc);
            lua_setfield(L, -2, "__gc");
        }
        if (call)
        {
            lua_pushcfunction(L, call);
            lua_setfield(L, -2, "__call");
        }
        lua_setmetatable(L, -2);
    }

    bool equal_metatable(lua_State* L, int stack_index, int ref_index)
    {
        lua_getmetatable(L, stack_index);
        lua_rawgeti(L, LUA_REGISTRYINDEX, ref_index);
        bool equal = lua_equal(L, -2, -1);
        lua_pop(L, 2);
        return equal;
    }

    int store_metatable(lua_State* L, const std::unordered_map<std::string, lua_CFunction>& map)
    {
        lua_newtable(L);
        for (const auto& func : map)
        {
            lua_pushcfunction(L, func.second);
            lua_setfield(L, -2, func.first.c_str());
        }
        return luaL_ref(L, LUA_REGISTRYINDEX);
    }

    void create_metatable(lua_State* L, const std::unordered_map<std::string, lua_CFunction>& map)
    {
        lua_newtable(L);
        for (const auto& func : map)
        {
            lua_pushcfunction(L, func.second);
            lua_setfield(L, -2, func.first.c_str());
        }
        lua_setmetatable(L, -2);
    }
}