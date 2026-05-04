#pragma once

#include "Beam_Internal.h"

namespace mmm
{
    namespace types { struct Phaser; }

    class Phaser : public Beam
    {
    public:
        static std::shared_ptr<Phaser> create(types::Entity* entity);
        ST3D_Colour getPhaserColour() const;
        void setPhaserColour(const ST3D_Colour& colour);
        int index(lua_State* L, const std::string& key) const override;
        int newindex(lua_State* L, const std::string& key) override;
    protected:
        explicit Phaser(types::Phaser* phaser);
    private:
        types::Phaser* getPhaser() const;
    };
}