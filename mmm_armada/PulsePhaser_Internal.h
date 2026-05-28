#pragma once

#include "Bullet.h"

namespace mmm
{
    namespace types { struct PulsePhaser; }

    class PulsePhaser : public Bullet
    {
    public:
        static std::shared_ptr<PulsePhaser> create(types::Entity* entity);

        ST3D_Colour getPhaserColour() const;
        void setPhaserColour(const ST3D_Colour& colour);
        int index(lua_State* L, const std::string& key) const override;
        int newindex(lua_State* L, const std::string& key) override;
    protected:
        explicit PulsePhaser(types::PulsePhaser* pulsePhaser);
    private:
        types::PulsePhaser* getPulsePhaser() const;
    };
}
