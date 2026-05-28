#include "Craft_Internal.h"
#include "CraftSystem_Internal.h"
#include "CraftClass_Internal.h"
#include "Type_Craft.h"
#include "Type_Entity.h"
#include "Type_CraftSystem.h"
#include "Type_CraftClass.h"
#include "LuaBinding.h"

namespace mmm
{
    namespace
    {
        const std::size_t Address_Explode = 0x004c6ab0;
        const std::size_t Address_GetAlertStatus = 0x004c9a20;
        const std::size_t Address_SetAlertStatus = 0x004c9a50;
        const std::size_t Address_GetSpecialWeaponAutonomy = 0x004c9ae0;
        const std::size_t Address_SetSpecialWeaponAutonomy = 0x004c9b10;
        const std::size_t Address_GetMovementAutonomy = 0x004c9b40;
        const std::size_t Address_SetMovementAutonomy = 0x004c9b70;
        const std::size_t Address_DisableEngines = 0x004c9ef0;
        const std::size_t Address_DisableLifeSupport = 0x004c9f80;
        const std::size_t Address_DisableShieldGenerator = 0x004ca010;
        const std::size_t Address_DisableWeapons = 0x004ca090;
        const std::size_t Address_DisableSensors = 0x004ca110;
        const std::size_t Address_PermanentDisableEngines = 0x004ca1a0;
        const std::size_t Address_PermanentDisableLifeSupport = 0x004ca230;
        const std::size_t Address_PermanentDisableShieldGenerator = 0x004ca2c0;
        const std::size_t Address_PermanentDisableWeapons = 0x004ca350;
        const std::size_t Address_PermanentDisableSensors = 0x004ca3e0;
        const std::size_t Address_GetShields = 0x004c8a50;
        const std::size_t Address_SetName = 0x004c1f00;
        const std::size_t Address_SetCrew = 0x004c83e0;
        const std::size_t Address_SetMaximumCrew = 0x004c8430;

        int craft_explode(lua_State* L)
        {
            auto self = get_entity<Craft>(L, 1);
            self->explode();
            return 0;
        }
    }

    std::shared_ptr<Craft> Craft::create(types::Entity* entity)
    {
        return std::shared_ptr<Craft>(new Craft(static_cast<types::Craft*>(entity)));
    }

    Craft::Craft(types::Craft* craft)
        : GameObject(craft)
    {
    }

    types::Craft* Craft::getCraft() const
    {
        return static_cast<types::Craft*>(getEntity());
    }

    std::string Craft::getName() const
    {
        types::Craft* craft = getCraft();
        if( craft && craft->m_pCraftName )
        {
            return craft->m_pCraftName;
        }
        return "";
    }

    float Craft::getShields() const
    {
        return (getCraft()->*memory_function<float (types::Craft::*)()>(Address_GetShields))();
    }

    float Craft::getShieldsValue() const
    {
        return getCraft()->m_curShields;
    }

    float Craft::getMaxShields() const
    {
        return getCraft()->m_maxShields;
    }

    eAlertStatus Craft::getAlertStatus() const
    {
        return (getCraft()->*memory_function<eAlertStatus (types::Craft::*)()>(Address_GetAlertStatus))();
    }

    eSpecialWeaponAutonomy Craft::getSpecialWeaponAutonomy() const
    {
        return (getCraft()->*memory_function< eSpecialWeaponAutonomy (types::Craft::*)() >( Address_GetSpecialWeaponAutonomy ))();
    }

    eMovementAutonomy Craft::getMovementAutonomy() const
    {
        return (getCraft()->*memory_function< eMovementAutonomy (types::Craft::*)() >( Address_GetMovementAutonomy ))();
    }

    float Craft::getImpulseSpeed() const
    {
        return getScriptInterface()->GetImpulseSpeed( getCraft()->m_entity_id );
    }

    float Craft::getCrew( ) const
    {
        return getCraft()->m_curCrew;
    }

    float Craft::getMaxCrew( ) const
    {
        return getCraft()->m_maxCrew;
    }

    int Craft::getSystems(lua_State* L) const
    {
        lua_newtable(L);
        craftsystem_new(L, std::make_shared<CraftSystem>(&getCraft()->m_pCraftSystem[0]));
        lua_setfield(L, -2, "shields");
        craftsystem_new(L, std::make_shared<CraftSystem>(&getCraft()->m_pCraftSystem[1]));
        lua_setfield(L, -2, "engines");
        craftsystem_new(L, std::make_shared<CraftSystem>(&getCraft()->m_pCraftSystem[2]));
        lua_setfield(L, -2, "weapons");
        craftsystem_new(L, std::make_shared<CraftSystem>(&getCraft()->m_pCraftSystem[3]));
        lua_setfield(L, -2, "lifeSupport");
        craftsystem_new(L, std::make_shared<CraftSystem>(&getCraft()->m_pCraftSystem[4]));
        lua_setfield(L, -2, "sensors");
        return 1;
    }

    std::shared_ptr<GameObjectClass> Craft::getClass() const
    {
        return createGameObjectClassPtr(getGameObject()->m_class);
    }

    void Craft::setName(const std::string& name)
    {
        (getCraft()->*memory_function<void (types::Craft::*)(const char*)>(Address_SetName))(name.c_str());
    }

    void Craft::setShields(float percentage)
    {
        getCraft()->m_curShields = getMaxShields() * percentage;
    }

    void Craft::setShieldsValue(float value)
    {
        getCraft()->m_curShields = value;
    }

    void Craft::setMaxShields(float value)
    {
        getCraft()->m_maxShields = value;
    }

    void Craft::setCrew(float value)
    {
        (getCraft()->*memory_function<void (types::Craft::*)( float )>(Address_SetCrew))(value);
    }

    void Craft::setMaxCrew(float value)
    {
        (getCraft()->*memory_function<void (types::Craft::*)( float )>(Address_SetMaximumCrew))(value);
    }

    void Craft::setAlertStatus(eAlertStatus status)
    {
        (getCraft()->*memory_function<void (types::Craft::*)(eAlertStatus)>(Address_SetAlertStatus ))(status);
    }

    void Craft::setSpecialWeaponAutonomy(eSpecialWeaponAutonomy autonomy)
    {
        (getCraft()->*memory_function<void (types::Craft::*)(eSpecialWeaponAutonomy)>(Address_SetSpecialWeaponAutonomy))(autonomy);
    }

    void Craft::setMovementAutonomy(eMovementAutonomy autonomy)
    {
        (getCraft()->*memory_function<void (types::Craft::*)(eMovementAutonomy)>(Address_SetMovementAutonomy))(autonomy);
    }

    void Craft::setSystemStatus(eCraftSystem system, bool state)
    {
        typedef void (types::Craft::*MemFunction)(bool);
        MemFunction function = 0;

        switch(system)
        {
        case Engines:
            function = memory_function<MemFunction>(Address_PermanentDisableEngines);
            break;
        case LifeSupport:
            function = memory_function<MemFunction>(Address_PermanentDisableLifeSupport);
            break;
        case Shields:
            function = memory_function<MemFunction>(Address_PermanentDisableShieldGenerator);
            break;
        case Weapons:
            function = memory_function<MemFunction>(Address_PermanentDisableWeapons);
            break;
        case Sensors:
            function = memory_function<MemFunction>(Address_PermanentDisableSensors);
            break;
        }

        if( function )
        {
            (getCraft()->*function)( !state );
        }
    }

    void Craft::setImpulseSpeed(float value)
    {
        getScriptInterface()->SetImpulseSpeed(getCraft()->m_entity_id, value);
    }

    void Craft::explode()
    {
        (getCraft()->*memory_function<void (types::Craft::*)()>(Address_Explode))();
    }

    void Craft::disableSystem(eCraftSystem system, float time)
    {
        typedef void (types::Craft::*MemFunction)(float);
        MemFunction function = 0;

        switch( system )
        {
        case Engines:
            function = memory_function<MemFunction>(Address_DisableEngines);
            break;
        case LifeSupport:
            function = memory_function<MemFunction>(Address_DisableLifeSupport);
            break;
        case Shields:
            function = memory_function<MemFunction>(Address_DisableShieldGenerator);
            break;
        case Weapons:
            function = memory_function<MemFunction>(Address_DisableWeapons);
            break;
        case Sensors:
            function = memory_function<MemFunction>(Address_DisableSensors);
            break;
        }

        if(function)
        {
            (getCraft()->*function)(time);
        }
    }

    int Craft::index(lua_State* L, const std::string& key) const
    {
        if (key == "alert")
        {
            lua_pushnumber(L, getAlertStatus());
            return 1;
        }
        else if (key == "crew")
        {
            lua_pushnumber(L, getCrew());
            return 1;
        }
        else if (key == "explode")
        {
            lua_pushcfunction(L, craft_explode);
            return 1;
        }
        else if (key == "impulseSpeed")
        {
            lua_pushnumber(L, getImpulseSpeed());
            return 1;
        }
        else if (key == "maxCrew")
        {
            lua_pushnumber(L, getMaxCrew());
            return 1;
        }
        else if (key == "maxShields")
        {
            lua_pushnumber(L, getMaxShields());
            return 1;
        }
        else if (key == "movementAutonomy")
        {
            lua_pushnumber(L, getMovementAutonomy());
            return 1;
        }
        else if (key == "name")
        {
            lua_pushstring(L, getName().c_str());
            return 1;
        }
        else if (key == "shields")
        {
            lua_pushnumber(L, getShields());
            return 1;
        }
        else if (key == "shieldsValue")
        {
            lua_pushnumber(L, getShieldsValue());
            return 1;
        }
        else if (key == "specialWeaponAutonomy")
        {
            lua_pushnumber(L, getSpecialWeaponAutonomy());
            return 1;
        }
        else if (key == "systems")
        {
            return getSystems(L);
        }
        return GameObject::index(L, key);
    }

    int Craft::newindex(lua_State* L, const std::string& key)
    {
        if (key == "alert")
        {
            setAlertStatus(static_cast<eAlertStatus>(lua_tonumber(L, 3)));
            return 0;
        }
        else if (key == "crew")
        {
            setCrew(lua_tonumber(L, 3));
            return 0;
        }
        else if (key == "impulseSpeed")
        {
            setImpulseSpeed(lua_tonumber(L, 3));
            return 0;
        }
        else if (key == "maxCrew")
        {
            setMaxCrew(lua_tonumber(L, 3));
            return 0;
        }
        else if (key == "maxShields")
        {
            setMaxShields(lua_tonumber(L, 3));
            return 0;
        }
        else if (key == "movementAutonomy")
        {
            setMovementAutonomy(static_cast<eMovementAutonomy>(lua_tonumber(L, 3)));
            return 0;
        }
        else if (key == "name")
        {
            setName(lua_tostring(L, 3));
            return 0;
        }
        else if (key == "shields")
        {
            setShields(lua_tonumber(L, 3));
            return 0;
        }
        else if (key == "shieldsValue")
        {
            setShieldsValue(lua_tonumber(L, 3));
            return 0;
        }
        else if (key == "specialWeaponAutonomy")
        {
            setSpecialWeaponAutonomy(static_cast<eSpecialWeaponAutonomy>(lua_tonumber(L, 3)));
            return 0;
        }
        return GameObject::newindex(L, key);
    }

    void craft_register(lua_State* L)
    {
        lua_newtable(L);
        create_enum(L, "AlertState",
            {
                { "Red", ALERT_STATUS_RED },
                { "Yellow", ALERT_STATUS_YELLOW },
                { "Green", ALERT_STATUS_GREEN }
            });
        create_enum(L, "MovementAutonomy",
            {
                { "Low", MOVEMENT_AUTONOMY_LOW },
                { "Medium", MOVEMENT_AUTONOMY_MED },
                { "High", MOVEMENT_AUTONOMY_HIGH }
            });
        create_enum(L, "WeaponAutonomy",
            {
                { "None", SPECIAL_WEAPON_AUTONOMY_NONE },
                { "Medium", SPECIAL_WEAPON_AUTONOMY_MED },
                { "High", SPECIAL_WEAPON_AUTONOMY_HIGH }
            });
        create_enum(L, "System",
            {
                { "Engines", Engines },
                { "LifeSupport", LifeSupport },
                { "Shields", Shields },
                { "Weapons", Weapons },
                { "Sensors", Sensors }
            });
        lua_setglobal(L, "Craft");
    }
}