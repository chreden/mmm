#include "ScrapClass_Internal.h"
#include "Type_ScrapClass.h"

namespace mmm
{
    ScrapClass::ScrapClass(types::ScrapClass* obj)
        : TerrainObjectClass(obj)
    {
    }

    types::ScrapClass* ScrapClass::getScrapClass() const
    {
        return static_cast<types::ScrapClass*>(getClass());
    }

    float ScrapClass::getRotationSpeed() const
    {
        return getScrapClass()->m_rotation_speed;
    }

    void ScrapClass::setRotationSpeed(float value)
    {
        getScrapClass()->m_rotation_speed = value;
    }

    int ScrapClass::index(lua_State* L, const std::string& key) const
    {
        if (key == "rotationSpeed")
        {
            lua_pushnumber(L, getRotationSpeed());
            return 1;
        }
        return TerrainObjectClass::index(L, key);
    }

    int ScrapClass::newindex(lua_State* L, const std::string& key)
    {
        if (key == "rotationSpeed")
        {
            setRotationSpeed(lua_tonumber(L, 3));
            return 1;
        }
        return TerrainObjectClass::newindex(L, key);
    }
}
