//Notes - in Fleet Operations it seems that the repair ship uses a weapon
//instead of just repairing via the class. This means I will either have to
//go via the carrier or just not support this for fleet ops, or say that
//they need to do it manually.

#include "RepairShip_Internal.h"
#include "RepairShipClass_Internal.h"
#include "Type_RepairShip.h"
#include "Type_RepairShipClass.h"
#include "MemRaider.h"

namespace mmm
{
    std::shared_ptr<RepairShip> RepairShip::create(types::Entity* entity)
    {
        return std::shared_ptr<RepairShip>(new RepairShip(static_cast<types::RepairShip*>(entity)));
    }

    RepairShip::RepairShip(types::RepairShip* ship)
        : Craft(ship)
    {
    }

    types::RepairShip* RepairShip::getRepairShip() const
    {
        return static_cast<types::RepairShip*>(getEntity());
    }

    std::shared_ptr<Entity> RepairShip::getRepairTarget() const
    {
        const types::RepairShip* const ship = getRepairShip();
        return createEntityPtr( GetEntity<types::Entity>( memraider::MrNode( ship->aiProcess ).get<int>( 0x1ac ) ) );
    }

    void RepairShip::setRepairTarget(const std::shared_ptr<Entity>& ent)
    {
        if (ent->isType(Entity_Craft))
        {
            getRepairShip()->m_pCraft = static_cast<types::Craft*>(ent->getEntity());
        }
    }

    int RepairShip::index(lua_State* L, const std::string& key) const
    {
        if (key == "repairTarget")
        {
            return entity_new(L, getRepairTarget());
        }
        return Craft::index(L, key);
    }

    int RepairShip::newindex(lua_State* L, const std::string& key)
    {
        if (key == "repairTarget")
        {
            setRepairTarget(get_entity<Entity>(L, 2));
            return 0;
        }
        return Craft::newindex(L, key);
    }
}
