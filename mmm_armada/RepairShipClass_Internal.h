#pragma once

#include "CraftClass_Internal.h"

namespace mmm
{
    namespace types
    {
        struct RepairShipClass;
    }

    class RepairShipClass : public CraftClass
    {
    public:
        static RepairShipClassPtr create(types::GameObjectClass* ptr);
        float getRepairRate() const;
        void setRepairRate(float value);
        int index(lua_State* L, const std::string& key) const override;
        int newindex(lua_State* L, const std::string& key) override;
    private:
        explicit RepairShipClass(types::RepairShipClass* ship);
        types::RepairShipClass* getRepairShipClass() const;
    };
}
