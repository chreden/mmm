#include "Type_GameObjectClass.h"

#include "GameObjectClass_Internal.h"
    #include "CraftClass_Internal.h"
        #include "ColonyClass_Internal.h"
        #include "RepairShipClass_Internal.h"
        #include "ProducerClass_Internal.h"

#include "MemRaider.h"
#include "LuaBinding.h"

namespace mmm
{
    namespace
    {
        const std::size_t Function_GetODF = 0x004ce370;

        int gameobjectclass_metatable{ LUA_NOREF };

        int gameobjectclass_index(lua_State* L)
        {
            auto self = get_userdata<std::shared_ptr<GameObjectClass>>(L, 1);
            return self->index(L, lua_tostring(L, 2));
        }

        int gameobjectclass_newindex(lua_State* L)
        {
            auto self = get_userdata<std::shared_ptr<GameObjectClass>>(L, 1);
            return self->newindex(L, lua_tostring(L, 2));
        }

        int gameobjectclass_gc(lua_State* L)
        {
            cleanup_userdata<std::shared_ptr<GameObjectClass>>(L, 1);
            return 0;
        }
    }

    std::shared_ptr<GameObjectClass> GameObjectClass::create(types::GameObjectClass* ptr)
    {
        return std::shared_ptr<GameObjectClass>(new GameObjectClass(ptr));
    }

    GameObjectClass::GameObjectClass(types::GameObjectClass* goClass)
        : class_(goClass)
    {
    }

    GameObjectClass::~GameObjectClass()
    {
    }

    std::string GameObjectClass::getLabel() const
    {
        return class_->label;
    }

    std::string GameObjectClass::getUnitString() const
    {
        return class_->unitString;
    }

    long GameObjectClass::getMaxSpecialEnergy() const
    {
        return class_->maxSpecialEnergy;
    }

    std::string GameObjectClass::getODF() const
    {
        return (class_->*memory_function<char* (types::GameObjectClass::*)()>(Function_GetODF))();
    }

    void GameObjectClass::setUnitString(const std::string& name)
    {
        std::size_t length = name.size() > 0x3F ? 0x3F : name.size();
        memcpy( class_->unitString, name.c_str(), length );
        class_->unitString[length] = 0;
    }

    void GameObjectClass::setMaxSpecialEnergy(long value)
    {
        class_->maxSpecialEnergy = value;
    }

    types::GameObjectClass* GameObjectClass::getClass() const
    {
        return class_;
    }

    std::shared_ptr<GameObjectClass> createGameObjectClassPtr(types::GameObjectClass* ptr)
    {
        //In order to spawn the correct type of entity, we must actually find out what the thing is.
        //We then call the function dependent on this.
        if( isGameObjectClass( ptr ) )
        {
            if( isTerrainObjectClass( ptr ) )
            {
                if( isAreaEffectObjectClass( ptr ) )
                {
                    if( isWormholeClass( ptr ) )
                    {
                        //return WormholeClass::create( ptr );
                    }
                    else if( isNebulaClass( ptr ) )
                    {
                        //return NebulaClass::create( ptr );
                    }
                    else if( isIonStormClass( ptr ) )
                    {
                        //return IonStormClass::create( ptr );
                    }
                    else if( isBlackholeClass( ptr ) )
                    {
                        //return BlackHoleClass::create( ptr );
                    }
                    //return AreaEffectObjectClass::create( ptr );
                }
                if( isScrapClass( ptr ) )
                {
                    //return ScrapClass::create( ptr );
                }
                else if( isUtritiumBallClass( ptr ) )
                {
                    //return UtritiumBallClass::create( ptr );
                }
                else if( isBackgroundObjectClass( ptr ) )
                {
                    if( isBackgroundPlanetClass( ptr ) )
                    {
                        //return BackgroundPlanetClass::create( ptr );
                    }
                    //return BackgroundObjectClass::create( ptr );
                }
                else if( isLatinumNebulaClass( ptr ) )
                {
                    //return LatinumNebulaClass::create( ptr );
                }
                else if( isAsteroidFieldClass( ptr ) )
                {
                    //return AsteroidFieldClass::create( ptr );
                }
                //return TerrainObjectClass::create( ptr );
            }
            else if( isCraftClass( ptr ) )
            {
                if( isProducerClass( ptr ) )
                {
                    if( isPlanetClass( ptr ) )
                    {
                        //return PlanetClass::create( ptr );
                    }
                    else if( isMiningStationClass( ptr ) )
                    {
                        if( isTradingStationClass( ptr ) )
                        {
                            //return TradingStationClass::create( ptr );
                        }
                        //return MiningStationClass::create( ptr );
                    }
                    else if( isShipyardClass( ptr ) )
                    {
                        if( isStarbaseClass( ptr ) )
                        {
                            //return StarbaseClass::create( ptr );
                        }
                        //return ShipyardClass::create( ptr );
                    }
                    else if( isEvolverClass( ptr ) )
                    {
                        //return EvolverClass::create( ptr );
                    }
                    else if( isConstructionRigClass( ptr ) )
                    {
                        //return ConstructionRigClass::create( ptr );
                    }
                    else if( isResearchStationClass( ptr ) )
                    {
                        //return ResearchStationClass::create( ptr );
                    }
                    return ProducerClass::create( ptr );
                }
                else if( isFreighterClass( ptr ) )
                {
                    //return FreighterClass::create( ptr );
                }
                else if( isRepairShipClass( ptr ) )
                {
                    return RepairShipClass::create( ptr );
                }
                else if( isColonyClass( ptr ) )
                {
                    return ColonyClass::create( ptr );
                }
                else if( isResearchPodClass( ptr ) )
                {
                    //return ResearchPodClass::create( ptr );
                }
                else if( isCargoShipClass( ptr ) )
                {
                    //return CargoShipClass::create( ptr );
                }
                else if( isScavengerClass( ptr ) )
                {
                    //return ScavengerClass::create( ptr );
                }
                else if( isPlanetMiningBaseClass( ptr ) )
                {
                    //return PlanetMiningBaseClass::create( ptr );
                }
                else if( isSensorArrayClass( ptr ) )
                {
                    //return SensorArrayClass::create( ptr );
                }
                else if( isMineArrayClass( ptr ) )
                {
                    //return MineArrayClass::create( ptr );
                }
                return CraftClass::create( ptr );
            }
            else if( isConstructionObjectClass( ptr ) )
            {
                //return ConstructionObjectClass::create( ptr );
            }

            return GameObjectClass::create( ptr );
        }

        return {};
    }

    int GameObjectClass::index(lua_State* L, const std::string& key) const
    {
        if (key == "label")
        {
            lua_pushstring(L, getLabel().c_str());
            return 1;
        }
        else if (key == "name")
        {
            lua_pushstring(L, getUnitString().c_str());
            return 1;
        }
        else if (key == "odf")
        {
            lua_pushstring(L, getODF().c_str());
            return 1;
        }
        return 0;
    }

    int GameObjectClass::newindex(lua_State* L, const std::string& key)
    {
        if (key == "name")
        {
            setUnitString(lua_tostring(L, 2));
            return 0;
        }
        return 0;
    }

    int gameobjectclass_new(lua_State* L, const std::shared_ptr<GameObjectClass>& ptr)
    {
        create_userdata(L, ptr);
        assign_metatable(L, gameobjectclass_metatable);
        return 1;
    }

    void gameobjectclass_register(lua_State* L)
    {
        gameobjectclass_metatable = store_metatable(L,
            {
                { "__index", gameobjectclass_index },
                { "__newindex", gameobjectclass_newindex },
                { "__gc", gameobjectclass_gc }
            });
    }
}