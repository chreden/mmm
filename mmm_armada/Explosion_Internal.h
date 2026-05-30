#pragma once

#include "Entity_Internal.h"

namespace mmm
{
    namespace types
    {
        struct Explosion;
    }

    class Explosion : public Entity
    {
    public:
        explicit Explosion(types::Explosion* explosion);
        std::shared_ptr<Entity> getEntityResponsible() const;
        float getRadius() const;
        bool getSoundPlayed() const;
        types::Explosion* getExplosion() const;
        int index(lua_State* L, const std::string& key) const override;
    };
}
