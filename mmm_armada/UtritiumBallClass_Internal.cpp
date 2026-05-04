#include "UtritiumBallClass_Internal.h"
#include "Type_UtritiumBallClass.h"

namespace mmm
{
    UtritiumBallClass::UtritiumBallClass(types::UtritiumBallClass* type)
        : TerrainObjectClass(type)
    {

    }

    types::UtritiumBallClass* UtritiumBallClass::getUtritiumBallClass() const
    {
        return static_cast<types::UtritiumBallClass*>(getClass());
    }

    float UtritiumBallClass::getDamage() const
    {
        return getUtritiumBallClass()->m_damageValue;
    }

    float UtritiumBallClass::getRadius() const
    {
        return getUtritiumBallClass()->m_radius;
    }

    float UtritiumBallClass::getRotation() const
    {
        return getUtritiumBallClass()->m_rotation;
    }

    float UtritiumBallClass::getLifetime() const
    {
        return getUtritiumBallClass()->m_lifeTimer;
    }

    float UtritiumBallClass::getScalingCount() const
    {
        return getUtritiumBallClass()->m_scalingCount;
    }

    float UtritiumBallClass::getScalingStepSize() const
    {
        return getUtritiumBallClass()->m_scalingStepSize;
    }

    void UtritiumBallClass::setDamage(float value)
    {
        getUtritiumBallClass()->m_damageValue = value;
    }

    void UtritiumBallClass::setRadius(float value)
    {
        getUtritiumBallClass()->m_radius = value;
    }

    void UtritiumBallClass::setRotation(float value)
    {
        getUtritiumBallClass()->m_rotation = value;
    }

    void UtritiumBallClass::setLifetime(float value)
    {
        getUtritiumBallClass()->m_lifeTimer = value;
    }

    void UtritiumBallClass::setScalingStepSize(float value)
    {
        getUtritiumBallClass()->m_scalingStepSize = value;
    }

    void UtritiumBallClass::setScalingCount(float value)
    {
        getUtritiumBallClass()->m_scalingCount = value;
    }

    int UtritiumBallClass::index(lua_State* L, const std::string& key) const
    {
        if (key == "damage")
        {
            lua_pushnumber(L, getDamage());
            return 1;
        }
        else if (key == "radius")
        {
            lua_pushnumber(L, getRadius());
            return 1;
        }
        else if (key == "rotation")
        {
            lua_pushnumber(L, getRotation());
            return 1;
        }
        else if (key == "lifetime")
        {
            lua_pushnumber(L, getLifetime());
            return 1;
        }
        else if (key == "scalingStepSize")
        {
            lua_pushnumber(L, getScalingStepSize());
            return 1;
        }
        else if (key == "scalingCount")
        {
            lua_pushnumber(L, getScalingCount());
            return 1;
        }
        return TerrainObjectClass::index(L, key);
    }

    int UtritiumBallClass::newindex(lua_State* L, const std::string& key)
    {
        if (key == "damage")
        {
            setDamage(lua_tonumber(L, 3));
            return 0;
        }
        else if (key == "radius")
        {
            setRadius(lua_tonumber(L, 3));
            return 0;
        }
        else if (key == "rotation")
        {
            setRotation(lua_tonumber(L, 3));
            return 0;
        }
        else if (key == "lifetime")
        {
            setLifetime(lua_tonumber(L, 3));
            return 0;
        }
        else if (key == "scalingStepSize")
        {
            setScalingStepSize(lua_tonumber(L, 3));
            return 0;
        }
        else if (key == "scalingCount")
        {
            setScalingCount(lua_tonumber(L, 3));
            return 0;
        }
        return TerrainObjectClass::newindex(L, key);
    }
}
