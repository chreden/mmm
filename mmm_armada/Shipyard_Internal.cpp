#include "Shipyard_Internal.h"
#include "Type_Shipyard.h"
#include "Type_Entity.h"
#include "WormholeType.h"
#include "Wormhole.h"
#include "OrientedQueue.h"
#include "LuaBinding.h"

namespace mmm
{
    std::shared_ptr<Shipyard> Shipyard::create(types::Entity* entity)
    {
        return std::shared_ptr<Shipyard>(new Shipyard( static_cast<types::Shipyard*>(entity)));
    }

    Shipyard::Shipyard(types::Shipyard* shipyard)
        : Producer(shipyard)
    {
    }

    types::Shipyard* Shipyard::getShipyard() const
    {
        return static_cast<types::Shipyard*>(getEntity());
    }

    std::shared_ptr<Entity> Shipyard::getWormhole() const
    {
        return createEntityPtr(getShipyard()->m_pWormhole);
    }

    std::shared_ptr<Entity> Shipyard::getRepairingShip() const
    {
        return createEntityPtr(GetEntity<types::Entity>(getShipyard()->m_dockedShip));
    }

    Vector3 Shipyard::getRallyPoint() const
    {
        return getShipyard()->m_rallyPoint;
    }

    std::shared_ptr<OrientedQueue> Shipyard::getRepairQueue() const
    {
        return OrientedQueue::create(static_cast<types::OrientedQueue*>(getShipyard()->m_pRepairQueue));
    }

    void Shipyard::setWormhole(const std::shared_ptr<Entity>& wormhole)
    {
        if( wormhole || !wormhole->isType(Entity_Wormhole))
        {
            return;
        }
        getShipyard()->m_pWormhole = static_cast<types::Wormhole*>(wormhole->getEntity());
    }

    void Shipyard::setRallyPoint(const Vector3& point)
    {
        getShipyard()->m_rallyPoint = point;
    }

    int Shipyard::index(lua_State* L, const std::string& key) const
    {
        if (key == "rallyPoint")
        {
            return vector_new(L, getRallyPoint());
        }
        else if (key == "repairingShip")
        {
            return entity_new(L, getRepairingShip());
        }
        else if (key == "repairQueue")
        {
            return queue_new(L, getRepairQueue());
        }
        return Producer::index(L, key);
    }

    int Shipyard::newindex(lua_State* L, const std::string& key)
    {
        if (key == "rallyPoint")
        {
            setRallyPoint(get_userdata<Vector3>(L, 3));
            return 0;
        }
        return Producer::newindex(L, key);
    }
}
