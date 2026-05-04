#include "PhotonTorpedo_Internal.h"
#include "Type_PhotonTorpedo.h"
#include "LuaBinding.h"

namespace mmm
{
    PhotonTorpedoPtr PhotonTorpedo::create(types::Entity* entity)
    {
        return PhotonTorpedoPtr(new PhotonTorpedo(static_cast<types::PhotonTorpedo*>(entity)));
    }

    PhotonTorpedo::PhotonTorpedo(types::PhotonTorpedo* torpedo)
        : Missile(torpedo)
    {

    }

    ST3D_Colour PhotonTorpedo::getPhotonColour() const
    {
        return getPhotonTorpedo()->m_photonColor;
    }

    void PhotonTorpedo::setPhotonColour(const ST3D_Colour& colour)
    {
        getPhotonTorpedo()->m_photonColor = colour;
    }

    types::PhotonTorpedo* PhotonTorpedo::getPhotonTorpedo() const
    {
        return static_cast<types::PhotonTorpedo*>(getEntity());
    }

    int PhotonTorpedo::index(lua_State* L, const std::string& key) const
    {
        if (key == "color")
        {
            return colour_new(L, getPhotonColour());
        }
        return Missile::index(L, key);
    }

    int PhotonTorpedo::newindex(lua_State* L, const std::string& key)
    {
        if (key == "color")
        {
            setPhotonColour(get_userdata<ST3D_Colour>(L, 3));
            return 0;
        }
        return Missile::newindex(L, key);
    }
}
