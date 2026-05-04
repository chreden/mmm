#pragma once

#include "Bullet.h"

namespace mmm
{
    namespace types { struct Artillery; }

    class Artillery : public Bullet
    {
    public:
        static std::shared_ptr<Artillery> create(types::Entity* entity);
        ST3D_Colour getArtilleryColor() const;
        void setArtilleryColor(const ST3D_Colour& color);
        int index(lua_State* L, const std::string& key) const override;
        int newindex(lua_State* L, const std::string& key) override;
    protected:
        explicit Artillery(types::Artillery* artillery);
    private:
        types::Artillery* getArtillery() const;
    };
}
