#pragma once

#include "Craft_Internal.h"

namespace mmm
{
    namespace types
    {
        struct RepairShip;
    }

    class RepairShip : public Craft
    {
    public:
        static std::shared_ptr<RepairShip> create(types::Entity* entity);
        std::shared_ptr<Entity> getRepairTarget() const;
        void setRepairTarget(const std::shared_ptr<Entity>& ent);
        int index(lua_State* L, const std::string& key) const override;
        int newindex(lua_State* L, const std::string& key) override;
    protected:
        explicit RepairShip(types::RepairShip* ship);
    private:
        types::RepairShip* getRepairShip() const;
    };
}
