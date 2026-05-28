#pragma once

#include "Missile_Internal.h"

namespace mmm
{
    namespace types { struct PhotonTorpedo; }

    class PhotonTorpedo : public Missile
    {
    public:
        static std::shared_ptr<PhotonTorpedo> create(types::Entity* entity);
        virtual	~PhotonTorpedo(){};
        ST3D_Colour getPhotonColour() const;
        void setPhotonColour(const ST3D_Colour& colour);
        int index(lua_State* L, const std::string& key) const override;
        int newindex(lua_State* L, const std::string& key) override;
    protected:
        explicit PhotonTorpedo(types::PhotonTorpedo* torpedo);
    private:
        types::PhotonTorpedo* getPhotonTorpedo() const;
    };
}
