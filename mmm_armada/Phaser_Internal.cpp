#include "Phaser_Internal.h"
#include "Type_Phaser.h"
#include "LuaBinding.h"

namespace mmm
{
    std::shared_ptr<Phaser> Phaser::create(types::Entity* entity)
    {
        return std::shared_ptr<Phaser>(new Phaser(static_cast<types::Phaser*> (entity)));
    }

    Phaser::Phaser(types::Phaser* phaser)
        : Beam(phaser)
    {
    }

    ST3D_Colour Phaser::getPhaserColour() const
    {
        return getPhaser()->m_phaserColor;
    }

    void Phaser::setPhaserColour(const ST3D_Colour& colour)
    {
        getPhaser()->m_phaserColor = colour;
    }

    types::Phaser* Phaser::getPhaser() const
    {
        return static_cast<types::Phaser*>(getEntity());
    }

    int Phaser::index(lua_State* L, const std::string& key) const
    {
        if (key == "color")
        {
            return colour_new(L, getPhaserColour());
        }
        return Beam::index(L, key);
    }

    int Phaser::newindex(lua_State* L, const std::string& key)
    {
        if (key == "color")
        {
            setPhaserColour(get_userdata<ST3D_Colour>(L, 3));
            return 0;
        }
        return Beam::newindex(L, key);
    }
}
