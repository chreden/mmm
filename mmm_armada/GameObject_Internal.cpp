#include "GameObject_Internal.h"
#include "GameObjectClass_Internal.h"
#include "Race_Internal.h"
#include "Team_Internal.h"
#include "Path_Internal.h"

#include "Type_GameObject.h"
#include "Type_Team.h"
#include "Type_Weapons.h"
#include "LuaBinding.h"

namespace mmm
{
    namespace
    {
        const std::size_t Address_SetHealth         = 0x004d2080;
        const std::size_t Address_SetMaximumHealth  = 0x004d2020;
        const std::size_t Address_GetOdfName        = 0x004d5620;
        const std::size_t Address_Cloak             = 0x004d5160;
        const std::size_t Address_Decloak           = 0x004d51b0;
        const std::size_t Address_CanCloak          = 0x004d51f0;
        const std::size_t Address_ImmediateCloak    = 0x004d03e0;
        const std::size_t Address_IsCloaked         = 0x004d03f0;
        const std::size_t Address_SetTeam           = 0x004d0f10;
        const std::size_t Address_SwapTeam          = 0x004d0ea0;
        const std::size_t Address_IsAIControlled    = 0x004d5290;
        const std::size_t Address_IsUnderAttack     = 0x004d1530; 
        const std::size_t Address_GiveOrderPos      = 0x004d1b50;
        const std::size_t Address_GiveOrderEnt      = 0x004d1af0;
        const std::size_t Address_GiveOrderClassPos = 0x004d1cb0;
        const std::size_t Address_GiveOrderPath     = 0x004d1b80;

        int gameobject_add_weapon(lua_State* L)
        {
            auto self = get_entity<GameObject>(L, 1);
            self->addWeapon(lua_tostring(L, 2));
            return 0;
        }

        int gameobject_cloak(lua_State* L)
        {
            auto self = get_entity<GameObject>(L, 1);
            self->cloak();
            return 0;
        }

        int gameobject_decloak(lua_State* L)
        {
            auto self = get_entity<GameObject>(L, 1);
            self->decloak();
            return 0;
        }

        int gameobject_give_order(lua_State* L)
        {
            auto self = get_entity<GameObject>(L, 1);
            const auto command = static_cast<AiCommand>(lua_tonumber(L, 2));

            if (lua_gettop(L) == 3)
            {
                if (is_vector(L, 3))
                {
                    self->giveOrder(command, get_userdata<Vector3>(L, 3));
                    return 0;
                }
                else if (is_entity(L, 3))
                {
                    self->giveOrder(command, get_entity<Entity>(L, 3));
                    return 0;
                }
                else if (is_path(L, 3))
                {
                    self->giveOrder(command, *get_userdata<std::shared_ptr<Path>>(L, 3));
                    return 0;
                }
                else if (lua_isnumber(L, 3))
                {
                    self->giveOrder(command, lua_tonumber(L, 3));
                    return 0;
                }
            }
            else if (lua_gettop(L) == 4)
            {
                if (lua_type(L, 3) == LUA_TSTRING)
                {
                    self->giveOrder(command, lua_tostring(L, 3), get_userdata<Vector3>(L, 4));
                    return 0;
                }
            }
            else if (lua_gettop(L) == 2)
            {
                self->giveOrder(command);
                return 0;
            }

            return 0;
        }

        int gameobject_immediate_cloak(lua_State* L)
        {
            auto self = get_entity<GameObject>(L, 1);
            self->immediateCloak();
            return 0;
        }
    }

    GameObjectPtr GameObject::create(types::Entity* entity)
    {
        return GameObjectPtr( new GameObject( static_cast<types::GameObject*>( entity ) ) ); 
    }

    GameObject::GameObject(types::GameObject* entity)
        : Entity(entity), ResourceInterface(entity)
    {
    }

    types::GameObject* GameObject::getGameObject() const
    {
        return static_cast<types::GameObject*>(getEntity());
    }

    std::string GameObject::getOdf() const
    {
        std::string odfname = (getGameObject()->*memory_function< const char* (types::GameObject::*) () >( Address_GetOdfName ))();
        std::transform( odfname.begin(), odfname.end(), odfname.begin(), tolower );
        return odfname;
    }

    std::string GameObject::getHandle() const
    {
        return getGameObject()->label;
    }

    bool GameObject::getInvincible() const
    {
        types::GameObject* object = getGameObject();
        return object->m_invincible != 0;
    }

    Vector3 GameObject::getVelocity() const
    {
        types::GameObject* object = getGameObject();
        return object->m_euler.m_vel;
    }

    std::shared_ptr<Team> GameObject::getTeam() const 
    {
        types::GameObject* object = getGameObject();
        return std::make_shared<Team>(object->teamNumber);
    }

    std::shared_ptr<Team> GameObject::getPerceivedTeam() const
    {
        types::GameObject* object = getGameObject();
        return std::make_shared<Team>(object->perceivedTeam);
    }

    float GameObject::getHealth() const
    {
        return getHitpoints() / getMaximumHealth();
    }

    float GameObject::getHitpoints() const
    {
        return getScriptInterface()->GetCurrentHealth(getID());
    }

    float GameObject::getMaximumHealth() const
    {
        return getScriptInterface()->GetMaxHealth(getID());
    }

    float GameObject::getSpecialEnergy() const
    {
        return getGameObject()->m_curSpecialEnergy;
    }

    float GameObject::getSpecialEnergyValue() const
    {
        return getSpecialEnergy() * getMaxSpecialEnergy();
    }

    float GameObject::getMaxSpecialEnergy() const
    {
        return getGameObject()->m_maxSpecialEnergy;
    }

    std::shared_ptr<GameObjectClass> GameObject::getClass( ) const
    {
        return createGameObjectClassPtr(getGameObject()->m_class);
    }

    std::shared_ptr<Race> GameObject::getRace() const
    {
        return std::make_shared<Race>(getGameObject()->m_pRace);
    }

    bool GameObject::isDestroyed() const
    {
        types::GameObject* object = getGameObject();
        return object->m_is_destroyed;
    }

    bool GameObject::isUnderAttack() const
    {
        float interval = 5.0f;
        return (getGameObject()->*memory_function<bool (types::GameObject::*)(float) const>(Address_IsUnderAttack))(interval);
    }

    bool GameObject::canCloak() const
    {
        return (getGameObject()->*memory_function<bool (types::GameObject::*)()>(Address_CanCloak))();
    }

    bool GameObject::isCloaked() const
    {
        return (getGameObject()->*memory_function< bool (types::GameObject::*)()>(Address_IsCloaked))();
    }

    bool GameObject::isAiControlled() const
    {
        return (getGameObject()->*memory_function<bool (types::GameObject::*)()>(Address_IsAIControlled))();
    }

    void GameObject::setInvincible(bool value)
    {
        types::GameObject* object = getGameObject();
        object->m_invincible = value;
    }

    void GameObject::setHealth(float value)
    {
        (getGameObject()->*memory_function<void (types::GameObject::*)(float)>(Address_SetHealth))(value * getMaximumHealth());
    }

    void GameObject::setHitpoints(float value)
    {
        (getGameObject()->*memory_function<void (types::GameObject::*)(float)>(Address_SetHealth))(value);
    }

    void GameObject::setMaximumHealth(float value)
    {
        (getGameObject()->*memory_function<void (types::GameObject::*)(float)>(Address_SetMaximumHealth))(value);
    }

    void GameObject::setSpecialEnergy(float value)
    {
        getGameObject()->m_curSpecialEnergy = value * getMaxSpecialEnergy();
    }

    void GameObject::setMaxSpecialEnergy(float value)
    {
        getGameObject()->m_maxSpecialEnergy = value;
    }

    void GameObject::setSpecialEnergyValue(float value)
    {
        getGameObject()->m_maxSpecialEnergy = value;
    }

    void GameObject::setVelocity(const Vector3& vec)
    {
        getGameObject()->m_euler.m_vel = vec;
    }

    void GameObject::setTeam(const std::shared_ptr<Team>& team)
    {
        types::GameObject* object = getGameObject();
        object->teamNumber = team->getNumber();
        object->perceivedTeam = team->getNumber();
        object->m_pRace = team->getRace()->getRace();
    }

    void GameObject::setPerceivedTeam(const std::shared_ptr<Team>& team)
    {
        types::GameObject* object = getGameObject();
        object->perceivedTeam = team->getNumber();
        object->m_pRace = team->getRace()->getRace();
    }

    bool GameObject::getForceOntoMap() const
    {
        types::GameObject* object = getGameObject();
        return object->m_force_onto_map;
    }

    void GameObject::setForceOntoMap(bool value)
    {
        types::GameObject* object = getGameObject();
        object->m_force_onto_map = value;
    }

    void GameObject::cloak()
    {
        (getGameObject()->*memory_function<void (types::GameObject::*)()>(Address_Cloak))();
    }

    void GameObject::decloak()
    {
        (getGameObject()->*memory_function<void (types::GameObject::*)()>(Address_Decloak))();
    }

    void GameObject::immediateCloak()
    {
        (getGameObject()->*memory_function<void (types::GameObject::*)()>(Address_ImmediateCloak))();
    }

    void GameObject::giveOrder(AiCommand order, const Vector3& pos)
    {
        (getGameObject()->*memory_function<void (types::GameObject::*)( AiCommand, const Vector3&, long, bool )>(Address_GiveOrderPos))
            (order, pos, 0, false);
    }

    void GameObject::giveOrder(AiCommand order, const std::shared_ptr<Entity>& ent)
    {
        if(ent->isType(Entity_GameObject))
        {
            (getGameObject()->*memory_function< void (types::GameObject::*)(AiCommand, const types::GameObject*, long, bool)>(Address_GiveOrderEnt))
                ( order, std::static_pointer_cast<GameObject>(ent)->getGameObject(), 0, false );
        }
    }

    void GameObject::giveOrder( AiCommand order, const std::string& cls, const Vector3& pos )
    {
        std::string lowerClassName(cls);
        std::transform(lowerClassName.begin(), lowerClassName.end(), lowerClassName.begin(), ::tolower);

        void* objectClass = FindGameObjectClass(lowerClassName.c_str());
        if (objectClass)
        {
            (getGameObject()->*memory_function<void (types::GameObject::*)(AiCommand, void*, const Vector3&, bool)>(Address_GiveOrderClassPos))
                (order, objectClass, pos, false);
        }
    }

    void GameObject::giveOrder(AiCommand order, const Path& path)
    {
        (getGameObject()->*memory_function< void (types::GameObject::*)(AiCommand, types::AiPath*, bool, bool)>(Address_GiveOrderPath))
            (order, path.getPath(), true, false);
    }

    void GameObject::giveOrder(AiCommand order, long what)
    {
        getScriptInterface()->SetCommandWhatWhoParamVO(getGameObject()->m_entity_id,
                                                       order,
                                                       getGameObject()->m_entity_id,
                                                       what,
                                                       false);
    }

    void GameObject::giveOrder(AiCommand order)
    {
        getScriptInterface()->SetCommandWhatWhoParamVO(getGameObject()->m_entity_id,
                                                       order,
                                                       getGameObject()->m_entity_id,
                                                       0,
                                                       false);
    }

    void GameObject::addWeapon(const std::string& weapon)
    {
        struct cPrjID
        {
            int m_id;
        };

        cPrjID testID = { 0 };
        (testID.*memory_function<void (cPrjID::*)(const char*) >(0x006593c0))(weapon.c_str());

        void* wpn = (memory_function<void* (*)(const cPrjID&)>(0x00664850))(testID);

        types::Carrier* carrier = static_cast<types::Carrier*>(getGameObject()->carrier);
        (carrier->*memory_function<void (types::Carrier::*)(void*, unsigned char)>(0x006682d0))(wpn, 0);
    }

    ResourceInterface GameObject::getResourceInterface( ) const
    {
        return ResourceInterface(*this);
    }

    Vector3 GameObject::getAlpha() const
    {
        return getGameObject()->m_euler.alpha;
    }

    Vector3 GameObject::getOmega() const
    {
        return getGameObject()->m_euler.omega;
    }

    Vector3 GameObject::getAccel() const
    {
        return getGameObject()->m_euler.accel;
    }

    void GameObject::setAlpha(const Vector3& alpha)
    {
        getGameObject()->m_euler.alpha = alpha;
    }

    void GameObject::setOmega(const Vector3& omega)
    {
        getGameObject()->m_euler.omega = omega;
    }

    void GameObject::setAccel(const Vector3& accel)
    {
        getGameObject()->m_euler.accel = accel;
    }

    void GameObject::setRace(const std::shared_ptr<Race>& race)
    {
        getGameObject()->m_pRace = race->getRace();
    }

    int GameObject::index(lua_State* L, const std::string& key) const
    {
        if (key == "accel")
        {
            return vector_new(L, getAccel());
        }
        else if (key == "addWeapon")
        {
            lua_pushcfunction(L, gameobject_add_weapon);
            return 1;
        }
        else if (key == "aiControlled")
        {
            lua_pushboolean(L, isAiControlled());
            return 1;
        }
        else if (key == "alpha")
        {
            return vector_new(L, getAlpha());
        }
        else if (key == "canCloak")
        {
            lua_pushboolean(L, canCloak());
            return 1;
        }
        else if (key == "class")
        {
            return gameobjectclass_new(L, getClass());
        }
        else if (key == "cloak")
        {
            lua_pushcfunction(L, gameobject_cloak);
            return 1;
        }
        else if (key == "cloaked")
        {
            lua_pushboolean(L, isCloaked());
            return 1;
        }
        else if (key == "decloak")
        {
            lua_pushcfunction(L, gameobject_decloak);
            return 1;
        }
        else if (key == "destroyed")
        {
            lua_pushboolean(L, isDestroyed());
            return 1;
        }
        else if (key == "forceOntoMap")
        {
            lua_pushboolean(L, getForceOntoMap());
            return 1;
        }
        else if (key == "giveOrder")
        {
            lua_pushcfunction(L, gameobject_give_order);
            return 1;
        }
        else if (key == "hull")
        {
            lua_pushnumber(L, getHealth());
            return 1;
        }
        else if (key == "hullValue")
        {
            lua_pushnumber(L, getHitpoints());
            return 1;
        }
        else if (key == "immediateCloak")
        {
            lua_pushcfunction(L, gameobject_immediate_cloak);
            return 1;
        }
        else if (key == "invincible")
        {
            lua_pushboolean(L, getInvincible());
            return 1;
        }
        else if (key == "label")
        {
            lua_pushstring(L, getHandle().c_str());
            return 1;
        }
        else if (key == "maxHull")
        {
            lua_pushnumber(L, getMaximumHealth());
            return 1;
        }
        else if (key == "maxSpecialEnergy")
        {
            lua_pushnumber(L, getMaxSpecialEnergy());
            return 1;
        }
        else if (key == "odf")
        {
            lua_pushstring(L, getOdf().c_str());
            return 1;
        }
        if (key == "omega")
        {
            return vector_new(L, getOmega());
        }
        else if (key == "perceivedTeam")
        {
            return team_new(L, getPerceivedTeam());
        }
        else if (key == "player")
        {
            return team_new(L, getTeam());
        }
        else if (key == "race")
        {
            return race_new(L, getRace());
        }
        else if (key == "specialEnergy")
        {
            lua_pushnumber(L, getSpecialEnergy());
            return 1;
        }
        else if (key == "specialEnergyValue")
        {
            lua_pushnumber(L, getSpecialEnergyValue());
            return 1;
        }
        else if (key == "underAttack")
        {
            lua_pushboolean(L, isUnderAttack());
            return 1;
        }
        else if (key == "velocity")
        {
            return vector_new(L, getVelocity());
        }

        const auto res = ResourceInterface::index(L, key);
        if (res.has_value())
        {
            return res.value();
        }
        return Entity::index(L, key);
    }

    int GameObject::newindex(lua_State* L, const std::string& key)
    {
        if (key == "accel")
        {
            setAccel(get_userdata<Vector3>(L, 3));
            return 0;
        }
        else if (key == "alpha")
        {
            setAlpha(get_userdata<Vector3>(L, 3));
            return 0;
        }
        else if (key == "forceOntoMap")
        {
            setForceOntoMap(lua_toboolean(L, 3));
            return 0;
        }
        else if (key == "hull")
        {
            setHealth(lua_tonumber(L, 3));
            return 0;
        }
        else if (key == "hullValue")
        {
            setHitpoints(lua_tonumber(L, 3));
            return 0;
        }
        else if (key == "invincible")
        {
            setInvincible(lua_toboolean(L, 3));
            return 0;
        }
        else if (key == "maxHull")
        {
            setMaximumHealth(lua_tonumber(L, 3));
            return 0;
        }
        else if (key == "maxSpecialEnergy")
        {
            setMaxSpecialEnergy(lua_tonumber(L, 3));
            return 0;
        }
        else if (key == "perceivedTeam")
        {
            setPerceivedTeam(get_userdata<std::shared_ptr<Team>>(L, 3));
            return 0;
        }
        else if (key == "player")
        {
            setTeam(get_userdata<std::shared_ptr<Team>>(L, 3));
            return 0;
        }
        else if (key == "race")
        {
            setRace(get_userdata<std::shared_ptr<Race>>(L, 3));
            return 0;
        }
        else if (key == "specialEnergy")
        {
            setSpecialEnergy(lua_tonumber(L, 3));
            return 0;
        }
        else if (key == "specialEnergyValue")
        {
            setSpecialEnergyValue(lua_tonumber(L, 3));
            return 0;
        }
        else if (key == "omega")
        {
            setOmega(get_userdata<Vector3>(L, 3));
            return 0;
        }
        else if (key == "velocity")
        {
            setVelocity(get_userdata<Vector3>(L, 3));
            return 0;
        }

        const auto res = ResourceInterface::newindex(L, key);
        if (res.has_value())
        {
            return res.value();
        }
        return Entity::newindex(L, key);
    }

    void gameobject_register(lua_State* L)
    {
        lua_newtable(L);
        create_enum(L, "Order",
            {
                { "None", CMD_NONE },
                { "Default", CMD_DEFAULT },
                { "Select", CMD_SELECT },
                { "Stop", CMD_STOP },
                { "Go", CMD_GO },
                { "GoSingle", CMD_GO_SINGLE },
                { "Attack", CMD_ATTACK },
                { "SpecialAttack", CMD_SPECIAL_ATTACK },
                { "AnchoredAttack", CMD_ANCHORED_ATTACK },
                { "TransportAttack", CMD_TRANSPORT_ATTACK },
                { "Queue", CMD_QUEUE },
                { "Follow", CMD_FOLLOW },
                { "Formation", CMD_FORMATION },
                { "Transport", CMD_TRANSPORT },
                { "TransportSpecial", CMD_TRANSPORT_SPECIAL },
                { "Recrew", CMD_RECREW },
                { "SetRallyPoint", CMD_SET_RALLY_POINT },
                { "Repair", CMD_GET_REPAIR },
                { "Defend", CMD_DEFEND },
                { "CancelBuild", CMD_CANCEL_BUILD },
                { "Decommision", CMD_DECOMMISSION },
                { "Mine", CMD_MINE },
                { "SearchAndDestroy", CMD_SEARCH_AND_DESTROY },
                { "Guard", CMD_GUARD },
                { "Scout", CMD_SCOUT },
                { "Build", CMD_BUILD },
                { "Patrol", CMD_PATROL },
                { "RedAlert", CMD_RED_ALERT },
                { "YellowAlert", CMD_YELLOW_ALERT },
                { "GreenAlert", CMD_GREEN_ALERT },
                { "CancelBuildQueueItem", CMD_CANCEL_BUILD_QUEUE_ITEM },
                { "Wormhole", CMD_WORMHOLE },
                { "FormFormation", CMD_FORMFORMATION },
                { "GoRally", CMD_GORALLY },
                { "StartTrade", CMD_START_TRADE },
                { "EndTrade", CMD_END_TRADE },
                { "Trading", CMD_TRADING },
                { "GiveResource", CMD_GIVERESOURCE },
                { "Colonize", CMD_COLONIZE },
                { "RepairOther", CMD_REPAIR_OTHER },
                { "BuyResource", CMD_BUY_RESOURCE },
                { "SellResource", CMD_SELL_RESOURCE },
                { "SetFormation", CMD_SET_FORMATION },
                { "GoWarp", CMD_GO_WARP },
                { "GoWarpSingle", CMD_GO_WARP_SINGLE },
                { "SetAttackMode", CMD_SET_ATTACK_MODE },
                { "SpecialWeaponNone", CMD_SPECIAL_WEAPON_AUTONOMY_NONE },
                { "SpecialWeaponMedium", CMD_SPECIAL_WEAPON_AUTONOMY_MED },
                { "SpecialWeaponHigh", CMD_SPECIAL_WEAPON_AUTONOMY_HIGH },
                { "MoveLow", CMD_MOVE_LOW },
                { "MoveMedium", CMD_MOVE_MED },
                { "MoveHigh", CMD_MOVE_HIGH },
                { "WeaponQueue", CMD_WEAPON_QUEUE },
                { "GetSuperRepair", CMD_GET_SUPER_REPAIR },
                { "SetFormationOrientation", CMD_SET_FORMATION_ORIENTATION },
                { "RecycleMetal", CMD_RECYCLE_METAL },
                { "RecycleDilithium", CMD_RECYCLE_DILITHIUM }
            });
        lua_setglobal(L, "GameObject");
    }
}
