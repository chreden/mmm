#pragma once

#include "Entity_Internal.h"
#include "ResourceInterface_Internal.h"

namespace mmm
{
    namespace types
    {
        struct GameObject;
    }

    class Race;
    class Path;
    class Team;
    class GameObjectClass;

    class GameObject : public Entity, public ResourceInterface
    {
    public:
        static GameObjectPtr create( types::Entity* entity );
        virtual ~GameObject() = default;
        std::string getOdf() const;
        std::string getHandle() const;
        bool                getInvincible() const;
        Vector3       getVelocity() const;
        std::shared_ptr<Team> getTeam() const;
        std::shared_ptr<Team> getPerceivedTeam() const;
        float               getHealth() const;
        float               getHitpoints() const;
        float               getMaximumHealth() const;
        float               getSpecialEnergy() const;
        float               getSpecialEnergyValue() const;
        float               getMaxSpecialEnergy() const;
        bool                getForceOntoMap() const;
        virtual std::shared_ptr<GameObjectClass> getClass() const;
        std::shared_ptr<Race> getRace() const;
        void                setHealth(float value);
        void                setHitpoints(float value);
        void                setMaximumHealth(float value);
        void                setSpecialEnergy(float value);
        void                setMaxSpecialEnergy(float value);
        void                setSpecialEnergyValue(float value);
        bool                isDestroyed() const;
        bool                isUnderAttack() const;
        bool                canCloak() const;
        bool                isCloaked() const;
        bool                isAiControlled() const;
        void                setInvincible(bool value);
        void                setVelocity(const Vector3& vec);
        void                setTeam(const std::shared_ptr<Team>& team );
        void                setPerceivedTeam(const std::shared_ptr<Team>& team );
        void                setForceOntoMap(bool value);
        void                cloak();
        void                decloak();
        void                immediateCloak();
        void                giveOrder(AiCommand order, const Vector3& pos);
        void                giveOrder(AiCommand order, const std::shared_ptr<Entity>& ent);
        void                giveOrder(AiCommand order, const std::string& cls, const Vector3& pos);
        void                giveOrder(AiCommand order, const Path& path);
        void                giveOrder(AiCommand order, long value);
        void                giveOrder(AiCommand order);
        void                addWeapon(const std::string& weapon);
        types::GameObject*  getGameObject() const;
        ResourceInterface   getResourceInterface() const;
        Vector3 getAlpha() const;
        Vector3 getOmega() const;
        Vector3 getAccel() const;
        void setAlpha(const Vector3& alpha);
        void setOmega(const Vector3& omega);
        void setAccel(const Vector3& accel);
        void setRace(const std::shared_ptr<Race>& race);

        int index(lua_State* L, const std::string& key) const override;
        int newindex(lua_State* L, const std::string& key) override;
    protected:
        explicit GameObject(types::GameObject* entity);
    };

    void gameobject_register(lua_State* L);
}