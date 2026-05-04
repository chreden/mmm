#include "AreaEffectObjectClass_Internal.h"
#include "Type_AreaEffectObjectClass.h"

namespace mmm
{
    AreaEffectObjectClass::AreaEffectObjectClass(types::AreaEffectObjectClass* type)
        : TerrainObjectClass( type )
    {

    }

    types::AreaEffectObjectClass* AreaEffectObjectClass::getAreaEffectObjectClass() const
    {
        return static_cast<types::AreaEffectObjectClass*>( getClass() );
    }

    float AreaEffectObjectClass::getRadius() const
    {
        return getAreaEffectObjectClass()->m_radius;
    }

    void AreaEffectObjectClass::setRadius( float value )
    {
        getAreaEffectObjectClass()->m_radius = value;
    }

    int AreaEffectObjectClass::index(lua_State* L, const std::string& key) const
    {
        if (key == "radius")
        {
            lua_pushnumber(L, getRadius());
            return 1;
        }
        return TerrainObjectClass::index(L, key);
    }

    int AreaEffectObjectClass::newindex(lua_State* L, const std::string& key)
    {
        if (key == "radius")
        {
            setRadius(lua_tonumber(L, 3));
            return 0;
        }
        return TerrainObjectClass::newindex(L, key);
    }
}
