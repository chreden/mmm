#pragma once

#include "Producer.h"

namespace mmm
{
    namespace types
    {
        class Shipyard;
    }

    class OrientedQueue;
    class Shipyard : public Producer
    {
    public:
        static std::shared_ptr<Shipyard> create(types::Entity* entity);
        std::shared_ptr<Entity> getWormhole() const;
        std::shared_ptr<Entity> getRepairingShip() const;
        Vector3 getRallyPoint() const;
        std::shared_ptr<OrientedQueue> getRepairQueue() const;
        void setRallyPoint(const Vector3& point);
        void setWormhole(const std::shared_ptr<Entity>& wormhole);
        types::Shipyard* getShipyard() const;

        int index(lua_State* L, const std::string& key) const override;
        int newindex(lua_State* L, const std::string& key) override;
    protected:
        explicit Shipyard(types::Shipyard* shipyard);
    };
}
