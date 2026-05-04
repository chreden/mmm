#include "Artillery.h"
#include "Type_Artillery.h"
#include "LuaBinding.h"

namespace mmm
{
    std::shared_ptr<Artillery> Artillery::create(types::Entity* entity)
    {
        return std::shared_ptr<Artillery>(new Artillery(static_cast<types::Artillery*>(entity)));
    }

    Artillery::Artillery(types::Artillery* artillery)
        : Bullet(artillery)
    {

    }

    types::Artillery* Artillery::getArtillery() const
    {
        return static_cast<types::Artillery*>(getEntity());
    }

    ST3D_Colour Artillery::getArtilleryColor() const
    {
        return getArtillery()->m_photonColor;
    }

    void Artillery::setArtilleryColor(const ST3D_Colour& color)
    {
        getArtillery()->m_photonColor = color;
    }

    int Artillery::index(lua_State* L, const std::string& key) const
    {
        if (key == "color")
        {
            return colour_new(L, getArtilleryColor());
        }
        return Bullet::index(L, key);
    }

    int Artillery::newindex(lua_State* L, const std::string& key)
    {
        if (key == "color")
        {
            setArtilleryColor(get_userdata<ST3D_Colour>(L, 3));
            return 0;
        }
        return Bullet::newindex(L, key);
    }
}