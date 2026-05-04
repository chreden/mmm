#pragma once

#include "EntityReference.h"
#include "Entities.h"

namespace mmm
{
    struct Vector3;

    //Entity enumeration - this contains the types that we will allow, and 
    //have defined.
    enum eEntityType
    {
        Entity_Entity,
            Entity_GameObject,
                Entity_Craft,
                    Entity_CargoShip,
                    Entity_RepairShip,
                    Entity_Freighter,
                    Entity_Colony,
                    Entity_ResearchPod,
                    Entity_ResearchStation,
                    Entity_Scavenger,
                    Entity_PlanetMiningBase,
                    Entity_SensorArray,
                    Entity_MineArray,
                    Entity_Producer,
                        Entity_Planet,
                        Entity_Evolver,
                        Entity_MiningStation,
                            Entity_TradingStation,
                        Entity_Shipyard,
                            Entity_Starbase,
                    Entity_Constructor,
                Entity_TerrainObject,
                    Entity_AsteroidField,
                    Entity_Scrap,
                    Entity_LatinumNebula,
                    Entity_BackgroundObject,
                        Entity_BackgroundPlanet,
                    Entity_UtritiumBall,
                    Entity_AreaEffectObject,
                        Entity_IonStorm,
                        Entity_Wormhole,
                        Entity_Nebula,
                        Entity_BlackHole,
                Entity_ConstructionObject,
            Entity_Ordnance,
                Entity_Beam,
                    Entity_Phaser,
                Entity_BeamToggle,
                Entity_Missile,
                    Entity_PhotonTorpedo,
                Entity_Bullet,
                    Entity_Artillery,
                    Entity_PulsePhaser,
                Entity_Mine,
                    Entity_GravityMine,
                    Entity_AntimatterMine,
            Entity_Explosion,
            Entity_ResourceTransferInterface,
        Entity_ResourceContainer
    };

    namespace types
    {
        class Team;
        struct Entity;
    }

    class Team;

    class Entity : public std::enable_shared_from_this<Entity>
    {
    public:
        static std::shared_ptr<Entity> create(types::Entity* entity);
        virtual ~Entity(){};

        bool operator==(const std::shared_ptr<Entity>& entity) const;

        Vector3 getScale() const;
        Vector3 getPosition() const;
        int getID() const;
        bool getHide() const;
        bool canTeamSee(const Team& team) const;
        void setScale(const Vector3& scale);
        void setPosition(const Vector3& position);
        void replace(const std::string& odf);
        void setHide(bool value);
        Vector3 getForward() const;
        void setForward(const Vector3& fv);
        bool isType(eEntityType type) const;
        bool empty() const;
        types::Entity* getEntity() const;
        bool expired() const;
        bool isValid() const;
        bool hook(const std::string& id, EntityHook::Type type, int table, int function, int argument);
        bool unhook(const std::string& id);
        bool unhook(const std::shared_ptr<Hook>& hook);
        int getHooks(lua_State* L) const;
        unsigned long getType() const;

        // Lua methods:
        virtual int index(lua_State* L, const std::string& key) const;
        virtual int newindex(lua_State* L, const std::string& key);
    protected:
        explicit Entity(types::Entity* ent);
    private:
        std::shared_ptr<EntityReference> entityReference_;
    };

    //Function that creates the correct type of entity from the given inner entity pointer.
    std::shared_ptr<Entity> createEntityPtr(types::Entity* ptr);

    bool is_entity(lua_State* L, int index);
    template <typename T>
    std::shared_ptr<T> get_entity(lua_State* L, int index);
    int entity_new(lua_State* L, const std::shared_ptr<Entity>& entity);
    void entity_register( lua_State* state );
}

#include "Entity_Internal.inl"
