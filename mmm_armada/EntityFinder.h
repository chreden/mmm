#pragma once

#include "Entity_Internal.h"
#include "EntityFinderFilter.h"

namespace mmm
{
    class Entity;
    class EntityFinder final
    {
    public:
        explicit EntityFinder(lua_State* L);
        explicit EntityFinder(lua_State* L, int index);
        int find() const;
        int find(int max) const;
        int find_one() const;
    private:
        void inner_find(std::vector<std::shared_ptr<Entity>>& results, int max = -1) const;

        std::vector<std::shared_ptr<EntityFinderFilter>> _filters;
        lua_State* _L{ nullptr };
    };

    void entityfinder_register(lua_State* L);
}
