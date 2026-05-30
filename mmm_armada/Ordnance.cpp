#include "Ordnance.h"
#include "Team_Internal.h"
#include "OrdnanceType.h"
#include "OrdnanceDamage.h"

namespace mmm
{
    Ordnance::Ordnance(types::Ordnance* ordnance)
        : Entity(ordnance)
    {
    }

    types::Ordnance* Ordnance::getOrdnance() const
    {
        return static_cast<types::Ordnance*>(getEntity());
    }

    std::shared_ptr<Team> Ordnance::getTeam() const
    {
        return std::make_shared<Team>(getOrdnance()->m_team_number);
    }

    Vector3 Ordnance::getTargetLocation() const
    {
        return getOrdnance()->targetLocationPos;
    }

    bool Ordnance::getReflected() const
    {
        return getOrdnance()->m_reflected;
    }

    std::shared_ptr<Entity> Ordnance::getOwner() const
    {
        return createEntityPtr(GetEntity<types::Entity>(getOrdnance()->ownerHandle));
    }

    std::shared_ptr<Entity> Ordnance::getTarget() const
    {
        return createEntityPtr(GetEntity<types::Entity>(getOrdnance()->targetHandle));
    }

    float Ordnance::getLifetime() const
    {
        return getOrdnance()->m_lifetime;
    }

    Vector3 Ordnance::getVelocity() const
    {
        return getOrdnance()->m_euler.m_vel;
    }

    std::shared_ptr<OrdnanceDamage> Ordnance::getDamage() const
    {
        return OrdnanceDamage::create(getOrdnance());
    }

    void Ordnance::setTarget(const std::shared_ptr<Entity>& target)
    {
        if(target)
        {
            getOrdnance()->targetHandle = target->getID();
        }
        else
        {
            getOrdnance()->targetHandle = 0;
        }
    }

    void Ordnance::setLifetime(float value)
    {
        getOrdnance()->m_lifetime = value;
    }

    void Ordnance::setVelocity(const Vector3& value)
    {
        getOrdnance()->m_euler.m_vel = value;
    }

    int Ordnance::index(lua_State* L, const std::string& key) const
    {
        if (key == "damage")
        {
            return ordnancedamage_new(L, getDamage());
        }
        else if (key == "lifetime")
        {
            lua_pushnumber(L, getLifetime());
            return 1;
        }
        else if (key == "owner")
        {
            return entity_new(L, getOwner());
        }
        else if (key == "ownerPlayer")
        {
            return team_new(L, getTeam());
        }
        else if (key == "reflected")
        {
            lua_pushboolean(L, getReflected());
            return 1;
        }
        else if (key == "targetEntity")
        {
            return entity_new(L, getTarget());
        }
        else if (key == "targetLocation")
        {
            return vector_new(L, getTargetLocation());
        }
        return Entity::index(L, key);
    }

    int Ordnance::newindex(lua_State* L, const std::string& key)
    {
        if (key == "lifetime")
        {
            setLifetime(lua_tonumber(L, 3));
            return 0;
        }
        else if (key == "targetEntity")
        {
            setTarget(get_entity<Entity>(L, 3));
            return 0;
        }
        return Ordnance::newindex(L, key);
    }
}
