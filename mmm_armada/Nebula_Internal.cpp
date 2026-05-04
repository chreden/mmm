#include "Nebula_Internal.h"
#include "Type_Nebula.h"

namespace mmm
{
    std::shared_ptr<Nebula> Nebula::create(types::Entity* entity)
    {
        return std::shared_ptr<Nebula>(new Nebula(static_cast<types::Nebula*>( entity )));
    }

    Nebula::Nebula(types::Nebula* nebula)
        : AreaEffectObject(nebula)
    {
    }

    bool Nebula::getCanBuildInNebula() const
    {
        return getNebula()->m_canWeBuildInHere;
    }

    void Nebula::setCanBuildInNebula(bool value)
    {
        getNebula()->m_canWeBuildInHere = value;
    }

    float Nebula::getDeltaRoll() const
    {
        return getNebula()->delta_roll;
    }

    float Nebula::getDeltaPitch() const
    {
        return getNebula()->delta_pitch;
    }

    float Nebula::getDeltaYaw() const
    {
        return getNebula()->delta_yaw;
    }

    void Nebula::setDeltaRoll(float value)
    {
        getNebula()->delta_roll = value;
    }

    void Nebula::setDeltaPitch(float value)
    {
        getNebula()->delta_pitch = value;
    }

    void Nebula::setDeltaYaw(float value)
    {
        getNebula()->delta_yaw = value;
    }

    types::Nebula* Nebula::getNebula() const
    {
        return static_cast<types::Nebula*>(getEntity());
    }

    int Nebula::index(lua_State* L, const std::string& key) const
    {
        if (key == "allowConstruction")
        {
            lua_pushboolean(L, getCanBuildInNebula());
            return 1;
        }
        else if (key == "deltaRoll")
        {
            lua_pushnumber(L, getDeltaRoll());
            return 1;
        }
        else if (key == "deltaYaw")
        {
            lua_pushnumber(L, getDeltaYaw());
            return 1;
        }
        else if (key == "deltaPitch")
        {
            lua_pushnumber(L, getDeltaPitch());
            return 1;
        }
        return AreaEffectObject::index(L, key);
    }

    int Nebula::newindex(lua_State* L, const std::string& key)
    {
        if (key == "allowConstruction")
        {
            setCanBuildInNebula(lua_toboolean(L, 3));
            return 0;
        }
        else if (key == "deltaRoll")
        {
            setDeltaRoll(lua_tonumber(L, 3));
            return 0;
        }
        else if (key == "deltaYaw")
        {
            setDeltaYaw(lua_tonumber(L, 3));
            return 0;
        }
        else if (key == "deltaPitch")
        {
            setDeltaPitch(lua_tonumber(L, 3));
            return 0;
        }
        return AreaEffectObject::newindex(L, key);
    }
}
