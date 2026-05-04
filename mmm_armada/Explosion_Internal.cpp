#include "Explosion_Internal.h"
#include "Type_Explosion.h"

namespace mmm
{
    Explosion::Explosion(types::Explosion* explosion)
        : Entity(explosion)
    {

    }

    types::Explosion* Explosion::getExplosion() const
    {
        return static_cast<types::Explosion*>(getEntity());
    }

    std::shared_ptr<Entity> Explosion::getEntityResponsible() const
    {
        return createEntityPtr(GetEntity<types::Entity>(getExplosion()->m_whoIsResponsibleForBlast));
    }

    float Explosion::getRadius() const
    {
        return getExplosion()->m_radius;
    }

    bool Explosion::getSoundPlayed() const
    {
        return getExplosion()->m_soundPlayed;
    }

    int Explosion::index(lua_State* L, const std::string& key) const
    {
        if (key == "entityResponsible")
        {
            return entity_new(L, getEntityResponsible());
        }
        else if (key == "radius")
        {
            lua_pushnumber(L, getRadius());
            return 1;
        }
        else if (key == "soundPlayed")
        {
            lua_pushboolean(L, getSoundPlayed());
            return 1;
        }
        return Entity::index(L, key);
    }
}
