#pragma once

#include "Entity_Internal.h"

namespace mmm
{
    namespace types
    {
        struct Ordnance;
    }

    class OrdnanceDamage;
    class Ordnance : public Entity
    {
    public:
        explicit Ordnance(types::Ordnance* ordnance);
        virtual ~Ordnance(){};

        std::shared_ptr<Team> getTeam() const;
        Vector3 getTargetLocation() const;
        bool getReflected() const;
        std::shared_ptr<Entity> getOwner() const;
        std::shared_ptr<Entity> getTarget() const;
        float getLifetime() const;
        Vector3 getVelocity() const;
        std::shared_ptr<OrdnanceDamage> getDamage() const;

        void setTarget(const std::shared_ptr<Entity>& target);
        void setLifetime(float value);
        void setVelocity(const Vector3& value);
        types::Ordnance* getOrdnance() const;

        int index(lua_State* L, const std::string& key) const override;
        int newindex(lua_State* L, const std::string& key) override;
    };
}
