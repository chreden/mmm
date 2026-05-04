#include "Entity_Internal.h"
#include "Type_Entity.h"
#include "BeamToggle.h"

#include "Team_Internal.h"

#include "Explosion_Internal.h"
#include "ConstructionObject_Internal.h"
#include "CraftSystem_Internal.h"
#include "Freighter_Internal.h"
#include "RepairShip_Internal.h"
#include "Colony_Internal.h"
#include "Evolver_Internal.h"
#include "ConstructionRig_Internal.h"
#include "BackgroundObject_Internal.h"
#include "BackgroundPlanet_Internal.h"
#include "BlackHole_Internal.h"
#include "ResearchPod_Internal.h"
#include "CargoShip_Internal.h"
#include "AsteroidField.h"
#include "Scavenger.h"
#include "PlanetMiningBase.h"
#include "SensorArray.h"
#include "MineArray.h"

    #include "MiningStation.h"
    #include "Planet_Internal.h"
    #include "ResourceTransferInterface.h"
        #include "Starbase_Internal.h"

    #include "IonStorm_Internal.h"
    #include "Nebula_Internal.h"
    #include "Wormhole.h"
    #include "Scrap_Internal.h"
    #include "UtritiumBall_Internal.h"
    #include "LatinumNebula_Internal.h"

#include "PulsePhaser_Internal.h"
#include "Phaser_Internal.h"
#include "PhotonTorpedo_Internal.h"
#include "Artillery.h"
#include "ResearchStation.h"

#include "ResourceInterface_Internal.h"

#include "TradingStation.h"

#include "Mine.h"
#include "AntimatterMine.h"
#include "GravityMine.h"

#include "Entities_Internal.h"
#include "LuaBinding.h"

namespace mmm
{
    namespace
    {
        const std::size_t Address_GetPosition = 0x004cfd90;
        const std::size_t Address_GetScale = 0x004cff40;
        const std::size_t Address_SetScale = 0x004cff20;
        const std::size_t Address_EnableScaling = 0x004cff50;
        const std::size_t Address_CanTeamSee = 0x004d0090;
        const Vector3 VectorUndefined(0, 0, 0);
    
        int entity_metatable{ LUA_NOREF };

        int entity_add(lua_State* L)
        {
            const std::string odf = lua_tostring(L, 1);
            if (lua_type(L, 2) == LUA_TNUMBER)
            {
                const auto result = Entities::add(odf, lua_tonumber(L, 2), get_userdata<Vector3>(L, 3));
                return entity_new(L, result);
            }

            const auto result = Entities::add(odf, get_userdata<std::shared_ptr<Team>>(L, 2), get_userdata<Vector3>(L, 3));
            return entity_new(L, result);
        }

        int entity_remove(lua_State* L)
        {
            auto entity = get_entity<Entity>(L, 1);
            lua_pushboolean(L, Entities::remove(entity));
            return 1;
        }

        int entity_class_index(lua_State* L)
        {
            const std::string key = lua_tostring(L, 2);

            if (key == "add")
            {
                lua_pushcfunction(L, entity_add);
                return 1;
            }
            else if (key == "remove")
            {
                lua_pushcfunction(L, entity_remove);
                return 1;
            }
            return 0;
        }

        int entity_class_newindex(lua_State* L)
        {
            return 0;
        }

        int entity_can_team_see(lua_State* L)
        {
            auto self = get_entity<Entity>(L, 1);
            auto team = get_userdata<std::shared_ptr<Team>>(L, 2);
            lua_pushboolean(L, self->canTeamSee(*team));
            return 1;
        }

        int entity_eq(lua_State* L)
        {
            auto self = get_entity<Entity>(L, 1);
            auto other = get_entity<Entity>(L, 2);
            lua_pushboolean(L, *self == other);
            return 1;
        }

        int entity_gc(lua_State* L)
        {
            cleanup_userdata<std::shared_ptr<EntityReference>>(L, 1);
            return 0;
        }

        int entity_hook(lua_State* L)
        {
            auto self = get_entity<Entity>(L, 1);
            const std::string id = lua_tostring(L, 2);
            const EntityHook::Type type = static_cast<EntityHook::Type>(lua_tointeger(L, 3));
            const int argument = luaL_ref(L, LUA_REGISTRYINDEX);
            const int function = luaL_ref(L, LUA_REGISTRYINDEX);
            const int table = luaL_ref(L, LUA_REGISTRYINDEX);
            lua_pushboolean(L, self->hook(id, type, table, function, argument));
            return 1;
        }

        int entity_istype(lua_State* L)
        {
            auto self = get_entity<Entity>(L, 1);
            eEntityType type = static_cast<eEntityType>(lua_tonumber(L, 2));
            lua_pushboolean(L, self->isType(type));
            return 1;
        }

        int entity_replace(lua_State* L)
        {
            auto self = get_entity<Entity>(L, 1);
            std::string odf = lua_tostring(L, 2);
            self->replace(odf);
            return 0;
        }

        int entity_unhook(lua_State* L)
        {
            auto self = get_entity<Entity>(L, 1);
            if (lua_type(L, 2) == LUA_TSTRING)
            {
                lua_pushboolean(L, self->unhook(lua_tostring(L, 2)));
                return 1;
            }
            lua_pushboolean(L, self->unhook(get_userdata<std::shared_ptr<Hook>>(L, 2)));
            return 1;
        }

        int entity_index(lua_State* L)
        {
            const auto self = get_entity<Entity>(L, 1);
            const std::string key = lua_tostring(L, 2);
            return self->index(L, key);
        }

        int entity_newindex(lua_State* L)
        {
            auto self = get_entity<Entity>(L, 1);
            return self->newindex(L, lua_tostring(L, 2));
        }
    }

    std::shared_ptr<Entity> Entity::create(types::Entity* entity)
    {
        return std::shared_ptr<Entity>(new Entity(entity));
    }

    Entity::Entity(types::Entity* ent)
        : entityReference_(EntityReference::create(ent))
    {
    }

    bool Entity::operator==(const std::shared_ptr<Entity>& entity) const
    {
        return entity && getEntity() == entity->getEntity();
    }

    types::Entity* Entity::getEntity() const
    {
        return entityReference_->getEntity();
    }

    Vector3 Entity::getScale() const
    {
        if (getEntity())
        {
            return (getEntity()->*memory_function<const Vector3& (types::Entity::*)() const>(Address_GetScale))();
        }
        return VectorUndefined;
    }

    Vector3 Entity::getPosition() const
    {
        if (getEntity())
        {
            typedef const Vector3& (types::Entity::*MemFunction)() const;
            MemFunction function = memory_function< MemFunction >(Address_GetPosition);
            return (getEntity()->*function)();
        }
        return VectorUndefined;
    }

    int Entity::getID() const
    {
        if (getEntity())
        {
            return getEntity()->m_entity_id;
        }
        return 0;
    }

    bool Entity::canTeamSee(const Team& team) const
    {
        if (getEntity())
        {
            return getEntity()->m_isVisible & (1 << team.getNumber());
        }
        return false;
    }

    void Entity::setScale(const Vector3& scale)
    {
        if (getEntity())
        {
            (getEntity()->*memory_function<void (types::Entity::*)(bool)>(Address_EnableScaling))
                (true);
            (getEntity()->*memory_function<void (types::Entity::*)(const Vector3&)>(Address_SetScale))
                (scale);
        }
    }

    void Entity::setPosition(const Vector3& pos)
    {
        if (getEntity())
        {
            getEntity()->SetOrigin(pos);
            if (types::isGameObject(getEntity()))
            {
                types::GameObject* object = static_cast<types::GameObject*>(getEntity());
                object->m_position = pos;
            }
        }
    }

    Vector3 Entity::getForward() const
    {
        return getEntity()->GetTransform().forward;
    }

    void Entity::setForward(const Vector3& fv)
    {
        if(getEntity())
        {
            getEntity()->SetForward(fv);
        }
    }

    void Entity::replace(const std::string& odf)
    {
        if (getEntity())
        {
            entityReference_ = EntityReference::create(GetEntity<types::Entity>(
                getScriptInterface()->ReplaceObject(getID(), const_cast<char*>(odf.c_str()))));
        }
    }

    void Entity::setHide(bool value)
    {
        getEntity()->m_disable_render = value;
    }

    bool Entity::getHide() const
    {
        return getEntity()->m_disable_render;
    }

    bool Entity::empty() const
    {
        return getEntity() == nullptr;
    }

    bool Entity::expired() const
    {
        return getEntity() && getEntity()->m_expired;
    }

    bool Entity::isValid() const
    {
        auto newEntity(createEntityPtr(getEntity()));
        return newEntity != nullptr;
    }

    bool Entity::isType(eEntityType type) const
    {
        types::Entity* ent = getEntity();

        switch( type )
        {
        case Entity_Entity:
            return true;
            break;
        case Entity_GameObject:
            return types::isGameObject( ent );
            break;
        case Entity_ConstructionObject:
            return types::isConstructionObject( ent );
            break;
        case Entity_Craft:
            return types::isCraft( ent ); 
            break;
        case Entity_PlanetMiningBase:
            return types::isCraft( ent ) &&
                   types::isPlanetMiningBase( ent );
            break;
        case Entity_CargoShip:
            return types::isCargoShip( ent );
            break;
        case Entity_SensorArray:
            return types::isSensorArray( ent );
            break;
        case Entity_MineArray:
            return types::isCraft( ent ) &&
                   types::isMineArray( ent );
            break;
        case Entity_Scavenger:
            return types::isScavenger( ent );
            break;
        case Entity_ResearchStation:
            return types::isResearchStation( ent );
            break;
        case Entity_ResearchPod:
            return types::isResearchPod( ent );
            break;
        case Entity_Colony:
            return types::isCraft( ent ) &&
                    types::isColony( ent );
            break;
        case Entity_Planet:
            return types::isPlanet( ent );
            break;
        case Entity_Producer:
            return types::isProducer( ent );
            break;
        case Entity_ResourceContainer:
            return types::isResourceContainer( ent );
            break;
        case Entity_BackgroundObject:
            return types::isBackgroundObject( ent );
            break;
        case Entity_BackgroundPlanet:
            return types::isBackgroundPlanet( ent );
            break;
        case Entity_RepairShip:
            return types::isRepairShip( ent );
            break;
        case Entity_Freighter:
            return types::isFreighter( ent );
            break;
        case Entity_Evolver:
            return types::isProducer( ent ) && 
                    types::isEvolver( ent );
            break;
        case Entity_BlackHole:
            return types::isBlackhole( ent );
            break;
        case Entity_Constructor:
            return types::isConstructor( ent );
            break;
        case Entity_Starbase:
            return types::isStarbase( ent );
            break;
        case Entity_MiningStation:
            return types::isMiningStation( ent );
            break;
        case Entity_TradingStation:
            return types::isMiningStation(ent) &&
                   types::isTradingStation( ent );
            break;
        case Entity_Wormhole:
            return types::isWormhole( ent );
            break;
        case Entity_LatinumNebula:
            return types::isLatinumNebula( ent );
            break;
        case Entity_TerrainObject:
            return types::isTerrainObject( ent );
            break;
        case Entity_AsteroidField:
            return types::isAsteroidField( ent );
            break;
        case Entity_UtritiumBall:
            return types::isUtritiumBall( ent );
            break;
        case Entity_Scrap:
            return types::isTerrainObject(ent) &&
                    types::isScrap( ent );
            break;
        case Entity_AreaEffectObject:
            return types::isAreaEffectObject( ent );
            break;
        case Entity_Nebula:
            return types::isNebula( ent );
            break;
        case Entity_Shipyard:
            return types::isShipyard( ent );
            break;
        case Entity_IonStorm:
            return types::isIonStorm( ent );
            break;
        case Entity_Ordnance:
            return types::isOrdnance( ent );
            break;
        case Entity_Beam:
            return types::isBeam( ent );
            break;
            case Entity_Phaser:
                return types::isBeam( ent ) &&
                            types::isPhaser( ent );
                break;
        case Entity_BeamToggle:
            return types::isBeamToggle( ent );
            break;
        case Entity_Missile:
            return types::isMissile( ent );
            break;
            case Entity_PhotonTorpedo:
                return types::isMissile( ent ) &&
                       types::isPhotonTorpedo( ent );
                break;
        case Entity_Bullet:
            return types::isBullet( ent );
            break;
            case Entity_Artillery:
                return types::isBullet( ent ) &&
                       types::isArtillery( ent );
            case Entity_PulsePhaser:
                return types::isBullet( ent ) &&
                       types::isPulsePhaser( ent );
                break;
        case Entity_Mine:
            return types::isMine(ent);
            break;
            case Entity_GravityMine:
                return types::isMine(ent) &&
                       types::isGravityMine( ent );
                break;
            case Entity_AntimatterMine:
                return types::isMine(ent) &&
                       types::isAntimatterMine( ent );
                break;
        case Entity_Explosion:
            return types::isExplosion(ent);
            break;
        case Entity_ResourceTransferInterface:
            return types::isResourceTransfer( ent );
            break;
        }

        return false;
    }

    std::shared_ptr<Entity> createEntityPtr(types::Entity* ent)
    {
        if(!ent)
        {
            return {};
        }

        //In order to spawn the correct type of entity, we must actually find out what the thing is.
        //We then call the function dependent on this.
        if( isGameObject( ent ) )
        {
            if( isTerrainObject( ent ) )
            {
                if( isAreaEffectObject( ent ) )
                {
                    if( isWormhole( ent ) )
                    {
                        return Wormhole::create( ent );
                    }
                    else if( isNebula( ent ) )
                    {
                        return Nebula::create( ent );
                    }
                    else if( isIonStorm( ent ) )
                    {
                        return IonStorm::create( ent );
                    }
                    else if( isBlackhole( ent ) )
                    {
                        return BlackHole::create( ent );
                    }
                    return AreaEffectObject::create( ent );
                }
                if( isScrap( ent ) )
                {
                    return Scrap::create( ent );
                }
                else if( isUtritiumBall( ent ) )
                {
                    return UtritiumBall::create( ent );
                }
                else if( isBackgroundObject( ent ) )
                {
                    if( isBackgroundPlanet( ent ) )
                    {
                        return BackgroundPlanet::create( ent );
                    }
                    return BackgroundObject::create( ent );
                }
                else if( isLatinumNebula( ent ) )
                {
                    return LatinumNebula::create( ent );
                }
                else if( isAsteroidField( ent ) )
                {
                    return AsteroidField::create( ent );
                }
                return TerrainObject::create( ent );
            }
            else if( isCraft( ent ) )
            {
                if( isProducer( ent ) )
                {
                    if( isPlanet( ent ) )
                    {
                        return Planet::create( ent );
                    }
                    else if( isMiningStation( ent ) )
                    {
                        if( isTradingStation( ent ) )
                        {
                            return TradingStation::create( ent );
                        }
                        return MiningStation::create( ent );
                    }
                    else if( isShipyard( ent ) )
                    {
                        if( isStarbase( ent ) )
                        {
                            return Starbase::create( ent );
                        }
                        return Shipyard::create( ent );
                    }
                    else if( isEvolver( ent ) )
                    {
                        return Evolver::create( ent );
                    }
                    else if( isConstructor( ent ) )
                    {
                        return ConstructionRig::create( ent );
                    }
                    else if( isResearchStation( ent ) )
                    {
                        return ResearchStation::create( ent );
                    }
                    return Producer::create( ent );
                }
                else if( isFreighter( ent ) )
                {
                    return Freighter::create( ent );
                }
                else if( isRepairShip( ent ) )
                {
                    return RepairShip::create( ent );
                }
                else if( isColony( ent ) )
                {
                    return Colony::create( ent );
                }
                else if( isResearchPod( ent ) )
                {
                    return ResearchPod::create( ent );
                }
                else if( isCargoShip( ent ) )
                {
                    return CargoShip::create( ent );
                }
                else if( isScavenger( ent ) )
                {
                    return Scavenger::create( ent );
                }
                else if( isPlanetMiningBase( ent ) )
                {
                    return PlanetMiningBase::create( ent );
                }
                else if( isSensorArray( ent ) )
                {
                    return SensorArray::create( ent );
                }
                else if( isMineArray( ent ) )
                {
                    return MineArray::create( ent );
                }
                return Craft::create( ent );
            }
            else if( isConstructionObject( ent ) )
            {
                return ConstructionObject::create( ent );
            }

            return GameObject::create( ent );
        }
        else if( isOrdnance( ent ) )
        {
            if( isMissile( ent ) )
            {
                //chainpulsar
                //klingoncommandoteam
                //colonizerpod
                //shieldremovingtorpedo
                //computeroverride
                //polarontorpedo
                //manheimeffect
                //myorton
                //plasmacannon

                if( isPhotonTorpedo( ent ) )
                {
                    return PhotonTorpedo::create( ent );
                }
                
                return Missile::create( ent );
            }
            else if( isMine( ent ) )
            {
                if( isGravityMine( ent ) )
                {
                    return GravityMine::create( ent );
                }
                else if ( isAntimatterMine( ent ) )
                {
                    return AntimatterMine::create( ent );
                }
                return Mine::create( ent );
            }
            else if( isBeam( ent ) )
            {
                //transientrift
                //warpcoreoverload
                //clairvoyantlink
                //psionicinsanity
                //physconicblast
                //hologenerator
                //romulanspy
                //fedshieldemitter
                //containmentbreach
                //shieldgendisruptor
                //borgenergyemitter
                //miningbeam
                //borgbore
                //holoemitter
                //shieldremodulation
                //plasmaoverdrive
                //psionicdisruption
                //colonizingbem
                //utritiumbeam

                if( isPhaser( ent ) )
                {
                    return Phaser::create( ent );
                }
                return Beam::create( ent );
            }
            else if( isBeamToggle( ent ) )
            {
                //techassimbeam
                //shielddisruptor
                //energyshiedlconverter
                //resourcextractionbeam
                //tractorbeam
                //shieldinversion
                //holdingbeam
                //accelcannon
                return BeamToggle::create( ent );
            }
            else if( isBullet( ent ) )
            {
                //nanites
                //shieldharmonic
                //probetorpedo
                //ionstormtorpedo
                //microorganism
                //transwarpdrive
                //nebulaflux
                //repulsionfield
                //targetoverride

                if( isArtillery( ent ) )
                {
                    return Artillery::create( ent );
                }
                else if( isPulsePhaser( ent ) )
                {
                    return PulsePhaser::create( ent );
                }
                return Bullet::create( ent );
            }
            return Ordnance::create( ent );
        }
        else if( isExplosion( ent ) )
        {
            //FireballExplosion
                //Omega explosion?
            //ShockwaveExplosion
                //ShockwaveCannon
            return Explosion::create( ent );
        }
        
        return Entity::create( ent );
    }

    bool Entity::hook(const std::string& id, EntityHook::Type type, int table, int function, int argument)
    {
        return entityReference_->addHook(id, type, table, function, argument);
    }

    bool Entity::unhook(const std::string& id)
    {
        return entityReference_->unhook(id);
    }

    bool Entity::unhook(const std::shared_ptr<Hook>& hook)
    {
        return entityReference_->unhook(hook);
    }

    int Entity::getHooks(lua_State* L) const
    {
        return entityReference_->getHooks(L);
    }

    unsigned long Entity::getType() const
    {
        auto ent = getEntity();
        if (ent)
        {
            return ent->m_entityType;
        }
        return 0;
    }

    bool is_entity(lua_State* L, int index)
    {
        return equal_metatable(L, index, entity_metatable);
    }

    int Entity::index(lua_State* L, const std::string& key) const
    {
        if (key == "canPlayerSee")
        {
            lua_pushcfunction(L, entity_can_team_see);
            return 1;
        }
        else if (key == "forward")
        {
            return vector_new(L, getForward());
        }
        else if (key == "hide")
        {
            lua_pushboolean(L, getHide());
            return 1;
        }
        else if (key == "hook")
        {
            lua_pushcfunction(L, entity_hook);
            return 1;
        }
        else if (key == "hooks")
        {
            return getHooks(L);
        }
        else if (key == "id")
        {
            lua_pushinteger(L, getID());
            return 1;
        }
        else if (key == "isType")
        {
            lua_pushcfunction(L, entity_istype);
            return 1;
        }
        else if (key == "position")
        {
            return vector_new(L, getPosition());
        }
        else if (key == "replace")
        {
            lua_pushcfunction(L, entity_replace);
            return 1;
        }
        else if (key == "scale")
        {
            return vector_new(L, getScale());
        }
        else if (key == "type")
        {
            lua_pushnumber(L, getType());
            return 1;
        }
        else if (key == "unhook")
        {
            lua_pushcfunction(L, entity_unhook);
            return 1;
        }
        else if (key == "valid")
        {
            lua_pushboolean(L, isValid());
            return 1;
        }
        return 0;
    }

    int Entity::newindex(lua_State* L, const std::string& key)
    {
        if (key == "position")
        {
            setPosition(get_userdata<Vector3>(L, 3));
            return 0;
        }
        else if (key == "scale")
        {
            setScale(get_userdata<Vector3>(L, 3));
            return 0;
        }
        else if (key == "hide")
        {
            setHide(lua_toboolean(L, 3));
            return 0;
        }
        else if (key == "forward")
        {
            setForward(get_userdata<Vector3>(L, 3));
            return 0;
        }
        return 0;
    }

    int entity_new(lua_State* L, const std::shared_ptr<Entity>& entity)
    {
        create_userdata(L, EntityReference::create(entity->getEntity()));
        assign_metatable(L, entity_metatable);
        return 1;
    }

    void entity_register(lua_State* L)
    {
        lua_newtable(L);
        create_enum(L, "Type",
            {
                { "Entity", Entity_Entity },
                { "GameObject", Entity_GameObject },
                { "Craft", Entity_Craft },
                { "CargoShip", Entity_CargoShip },
                { "Colony", Entity_Colony },
                { "Freighter", Entity_Freighter },
                { "RepairShip", Entity_RepairShip },
                { "ResearchPod", Entity_ResearchPod },
                { "Scavenger", Entity_Scavenger },
                { "PlanetMiningBase", Entity_PlanetMiningBase },
                { "SensorArray", Entity_SensorArray },
                { "MineArray", Entity_MineArray },
                { "Producer", Entity_Producer },
                { "Evolver", Entity_Evolver },
                { "Planet", Entity_Planet },
                { "ConstructionRig", Entity_Constructor },
                { "ResearchStation", Entity_ResearchStation },
                { "Shipyard", Entity_Shipyard },
                { "Starbase", Entity_Starbase },
                { "MiningStation", Entity_MiningStation },
                { "TradingStation", Entity_TradingStation },
                { "TerrainObject", Entity_TerrainObject },
                { "AsteroidField", Entity_AsteroidField },
                { "Scrap", Entity_Scrap },
                { "LatinumNebula", Entity_LatinumNebula },
                { "BackgroundObject", Entity_BackgroundObject },
                { "BackgroundPlanet", Entity_BackgroundPlanet },
                { "UtritiumBall", Entity_UtritiumBall },
                { "AreaEffectObject", Entity_AreaEffectObject },
                { "Wormhole", Entity_Wormhole },
                { "Nebula", Entity_Nebula },
                { "IonStorm", Entity_IonStorm },
                { "BlackHole", Entity_BlackHole },
                { "ConstructionObject", Entity_ConstructionObject },
                { "Ordnance", Entity_Ordnance },
                { "Beam", Entity_Beam },
                { "Phaser", Entity_Phaser },
                { "BeamToggle", Entity_BeamToggle },
                { "Missile", Entity_Missile },
                { "PhotonTorpedo", Entity_PhotonTorpedo },
                { "Bullet", Entity_Bullet },
                { "Artillery", Entity_Artillery },
                { "PulsePhaser", Entity_PulsePhaser },
                { "Mine", Entity_Mine },
                { "AntimatterMine", Entity_AntimatterMine },
                { "GravityMine", Entity_GravityMine },
                { "Explosion", Entity_Explosion },
                { "ResourceInterface", Entity_ResourceContainer },
                { "ResourceTransferInterface", Entity_ResourceTransferInterface },
            });
        create_metatable(L,
            {
                { "__index", entity_class_index },
                { "__newindex", entity_class_newindex }
            });
        lua_setglobal(L, "Entity");

        entity_metatable = store_metatable(L,
            {
                { "__index", entity_index },
                { "__newindex", entity_newindex },
                { "__eq", entity_eq },
                { "__gc", entity_gc }
            });
    }
}
