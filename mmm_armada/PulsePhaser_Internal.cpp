#include "PulsePhaser_Internal.h"
#include "Type_PulsePhaser.h"
#include "LuaBinding.h"

namespace mmm
{
    std::shared_ptr<PulsePhaser> PulsePhaser::create(types::Entity* entity)
    {
        return std::shared_ptr<PulsePhaser>(new PulsePhaser(static_cast<types::PulsePhaser*>(entity)));
    }

    PulsePhaser::PulsePhaser(types::PulsePhaser* pulsePhaser)
        : Bullet(pulsePhaser)
    {

    }

    ST3D_Colour PulsePhaser::getPhaserColour() const
    {
        return getPulsePhaser()->m_phaserColour;
    }

    void PulsePhaser::setPhaserColour(const ST3D_Colour& colour)
    {
        getPulsePhaser()->m_phaserColour = colour;
    }

    types::PulsePhaser* PulsePhaser::getPulsePhaser() const
    {
        return static_cast<types::PulsePhaser*>(getEntity());
    }

    int PulsePhaser::index(lua_State* L, const std::string& key) const
    {
        if (key == "color")
        {
            return colour_new(L, getPhaserColour());
        }
        return Bullet::index(L, key);
    }

    int PulsePhaser::newindex(lua_State* L, const std::string& key)
    {
        if (key == "color")
        {
            setPhaserColour(get_userdata<ST3D_Colour>(L, 3));
            return 0;
        }
        return Bullet::newindex(L, key);
    }
}
