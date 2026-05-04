#include "LatinumNebulaClass_Internal.h"
#include "Type_LatinumNebulaClass.h"

namespace mmm
{
    LatinumNebulaClass::LatinumNebulaClass(types::LatinumNebulaClass* nebula)
        : TerrainObjectClass(nebula)
    {
    }

    float LatinumNebulaClass::getRotationSpeed() const
    {
        return getLatinumNebula()->m_rotationSpeed;
    }

    void LatinumNebulaClass::setRotationSpeed(float value)
    {
        getLatinumNebula()->m_rotationSpeed = value;
    }

    types::LatinumNebulaClass* LatinumNebulaClass::getLatinumNebula() const
    {
        return static_cast<types::LatinumNebulaClass*>(getClass());
    }

    int LatinumNebulaClass::index(lua_State* L, const std::string& key) const
    {
        if (key == "rotationSpeed")
        {
            lua_pushnumber(L, getRotationSpeed());
            return 1;
        }
        return TerrainObjectClass::index(L, key);
    }

    int LatinumNebulaClass::newindex(lua_State* L, const std::string& key)
    {
        if (key == "rotationSpeed")
        {
            setRotationSpeed(lua_tonumber(L, 3));
            return 0;
        }
        return TerrainObjectClass::newindex(L, key);
    }
}
