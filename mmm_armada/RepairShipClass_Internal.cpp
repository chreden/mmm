#include "RepairShipClass_Internal.h"
#include "Type_RepairShipClass.h"

namespace mmm
{
    std::shared_ptr<RepairShipClass> RepairShipClass::create(types::GameObjectClass* ptr)
    {
        return std::shared_ptr<RepairShipClass>(new RepairShipClass(static_cast<types::RepairShipClass*>(ptr)));
    }

    RepairShipClass::RepairShipClass(types::RepairShipClass* ship)
        : CraftClass(ship)
    {
    }

    types::RepairShipClass* RepairShipClass::getRepairShipClass() const
    {
        return static_cast<types::RepairShipClass*>(getClass());
    }

    float RepairShipClass::getRepairRate() const
    {
        return getRepairShipClass()->m_repairRate;
    }

    void RepairShipClass::setRepairRate(float value)
    {
        getRepairShipClass()->m_repairRate = value;
    }

    int RepairShipClass::index(lua_State* L, const std::string& key) const
    {
        if (key == "repairRate")
        {
            lua_pushnumber(L, getRepairRate());
            return 1;
        }
        return CraftClass::index(L, key);
    }

    int RepairShipClass::newindex(lua_State* L, const std::string& key)
    {
        if (key == "repairRate")
        {
            setRepairRate(lua_tonumber(L, 3));
            return 0;
        }
        return CraftClass::newindex(L, key);
    }
}
