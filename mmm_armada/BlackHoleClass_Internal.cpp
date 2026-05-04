#include "BlackHoleClass_Internal.h"
#include "Type_BlackHoleClass.h"

namespace mmm
{
    BlackHoleClass::BlackHoleClass(types::BlackHoleClass* type)
        : AreaEffectObjectClass(type)
    {
    }

    types::BlackHoleClass* BlackHoleClass::getBlackHoleClass() const
    {
        return static_cast<types::BlackHoleClass*>(getClass());
    }

    float BlackHoleClass::getGravityRadius() const
    {
        return getBlackHoleClass()->m_gravityRadius;
    }

    float BlackHoleClass::getEventRadius() const
    {
        return getBlackHoleClass()->m_eventRadius;
    }

    float BlackHoleClass::getGravityForce() const
    {
        return getBlackHoleClass()->m_gravityForce;
    }

    float BlackHoleClass::getRotation() const
    {
        return getBlackHoleClass()->m_rotation;
    }

    float BlackHoleClass::getScaleSize() const
    {
        return getBlackHoleClass()->m_scaleSize;
    }

    void BlackHoleClass::setGravityRadius(float value)
    {
        getBlackHoleClass()->m_gravityRadius = value;
    }

    void BlackHoleClass::setEventRadius(float value)
    {
        getBlackHoleClass()->m_eventRadius = value;
    }

    void BlackHoleClass::setGravityForce(float value)
    {
        getBlackHoleClass()->m_gravityForce = value;
    }

    void BlackHoleClass::setRotation(float value)
    {
        getBlackHoleClass()->m_rotation = value;
    }

    void BlackHoleClass::setScaleSize(float value)
    {
        getBlackHoleClass()->m_scaleSize = value;
    }

    int BlackHoleClass::index(lua_State* L, const std::string& key) const
    {
        if (key == "eventRadius")
        {
            lua_pushnumber(L, getEventRadius());
            return 1;
        }
        else if (key == "gravityForce")
        {
            lua_pushnumber(L, getGravityForce());
            return 1;
        }
        else if (key == "gravityRadius")
        {
            lua_pushnumber(L, getGravityRadius());
            return 1;
        }
        else if (key == "rotation")
        {
            lua_pushnumber(L, getRotation());
            return 1;
        }
        else if (key == "scaleSize")
        {
            lua_pushnumber(L, getScaleSize());
            return 1;
        }
        return TerrainObjectClass::index(L, key);
    }

    int BlackHoleClass::newindex(lua_State* L, const std::string& key)
    {
        if (key == "eventRadius")
        {
            setEventRadius(lua_tonumber(L, 3));
            return 0;
        }
        else if (key == "gravityForce")
        {
            setGravityForce(lua_tonumber(L, 3));
            return 0;
        }
        else if (key == "gravityRadius")
        {
            setGravityRadius(lua_tonumber(L, 3));
            return 0;
        }
        else if (key == "rotation")
        {
            setRotation(lua_tonumber(L, 3));
            return 0;
        }
        else if (key == "scaleSize")
        {
            setScaleSize(lua_tonumber(L, 3));
            return 0;
        }
        return TerrainObjectClass::newindex(L, key);
    }
}
