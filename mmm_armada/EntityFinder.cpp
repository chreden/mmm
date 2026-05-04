#include "EntityFinder.h"
#include "ScriptErrors.h"
#include "Entities_Internal.h"
#include "EntityFinderFilterFunction.h"
#include "EntityFinderFilterObject.h"
#include "LuaBinding.h"

namespace mmm
{
    namespace
    {
        int finder_gc(lua_State* L)
        {
            cleanup_userdata<std::shared_ptr<EntityFinder>>(L);
            return 0;
        }

        int finder_find(lua_State* L)
        {
            auto self = get_userdata<std::shared_ptr<EntityFinder>>(L, 1);
            if (lua_gettop(L) == 2 && lua_type(L, 2) == LUA_TNUMBER)
            {
                return self->find(lua_tonumber(L, 2));
            }
            return self->find();
        }

        int finder_find_one(lua_State* L)
        {
            auto self = get_userdata<std::shared_ptr<EntityFinder>>(L, 1);
            return self->find_one();
        }

        int finder_index(lua_State* L)
        {
            const auto team = get_userdata<std::shared_ptr<EntityFinder>>(L, 1);
            const std::string key = lua_tostring(L, 2);

            if (key == "find")
            {
                lua_pushcfunction(L, finder_find);
                return 1;
            }
            else if (key == "findOne")
            {
                lua_pushcfunction(L, finder_find_one);
                return 1;
            }

            return 0;
        }

        int entityfinder_call(lua_State* L)
        {
            auto finder_ptr = std::make_shared<EntityFinder>(L, 2);
            create_userdata(L, finder_ptr);
            create_metatable(L,
                {
                    { "__index", finder_index },
                    { "__gc", finder_gc }
                });
            return 1;
        }
    }

    EntityFinder::EntityFinder(lua_State* L)
        : _L(L)
    {
    }

    EntityFinder::EntityFinder(lua_State* L, int index)
        : _L(L)
    {
        lua_pushvalue(L, index);
        const int table_index = luaL_ref(L, LUA_REGISTRYINDEX);

        switch (lua_type(L, index))
        {
        case LUA_TTABLE:
            {
                // Class with evaluate 
                lua_getfield(L, index, "evaluate");
                if (lua_type(L, -1) == LUA_TFUNCTION)
                {
                    const int func = luaL_ref(L, LUA_REGISTRYINDEX);
                    const int table = luaL_ref(L, LUA_REGISTRYINDEX);
                    _filters.push_back(std::make_shared<EntityFinderFilterObject>(L, table, func));
                    break;
                }
                lua_pop(L, 1);

                // List of things:
                const int source = lua_gettop(L);
                lua_pushnil(L);
                while (lua_next(L, source) != 0)
                {
                    if (lua_type(L, -1) == LUA_TUSERDATA)
                    {
                        lua_getfield(L, index, "evaluate");
                        if (lua_type(L, -1) == LUA_TFUNCTION)
                        {
                            const int func = luaL_ref(L, LUA_REGISTRYINDEX);
                            const int table = luaL_ref(L, LUA_REGISTRYINDEX);
                            _filters.push_back(std::make_shared<EntityFinderFilterObject>(L, table, func));
                        }
                    }
                    else if (lua_type(L, -1) == LUA_TFUNCTION)
                    {
                        _filters.push_back(std::make_shared<EntityFinderFilterFunction>(L, luaL_ref(L, LUA_REGISTRYINDEX)));
                    }
                }
                break;
            }
        case LUA_TFUNCTION:
            {
                _filters.push_back(std::make_shared<EntityFinderFilterFunction>(L, table_index));
                break;
            }
        case LUA_TUSERDATA:
            {
                lua_getfield(L, index, "evaluate");
                if (lua_type(L, -1) == LUA_TFUNCTION)
                {
                    _filters.push_back(std::make_shared<EntityFinderFilterObject>(L, table_index, luaL_ref(L, LUA_REGISTRYINDEX)));
                }
            }
            break;
        }
    }

    int EntityFinder::find() const
    {
        return find(-1);
    }

    int EntityFinder::find(int max) const
    {
        std::vector<std::shared_ptr<Entity>> results;
        inner_find(results, max);

        lua_newtable(_L);
        const std::size_t Count = results.size();
        for (std::size_t e = 0; e < Count; ++e)
        {
            entity_new(_L, results[e]);
            lua_rawseti(_L, -2, e + 1);
        }
        return 1;
    }

    int EntityFinder::find_one() const
    {
        std::vector<std::shared_ptr<Entity>> results;
        inner_find(results, 1);
        if (results.empty())
        {
            lua_pushnil(_L);
            return 1;
        }
        return entity_new(_L, results[0]);
    }

    void EntityFinder::inner_find(std::vector<std::shared_ptr<Entity>>& results, int max) const
    {
        std::vector<std::shared_ptr<Entity>> entities;
        Entities::getActiveEntities(entities);

        const std::size_t Count = entities.size();
        const std::size_t FilterCount = _filters.size();
        for (int e = 0; e < Count; ++e)
        {
            auto entity = entities[e];

            // Don't use expired things because it causes trouble.
            if (entity->expired() || !entity->getEntity())
            {
                continue;
            }

            bool passes = true;

            //Check all filters.
            for (std::size_t f = 0; f < FilterCount; ++f)
            {
                if (!_filters[f]->call(entity))
                {
                    passes = false;
                    break;
                }
            }

            if (passes)
            {
                results.push_back(entity);
                if (max != -1 && results.size() == static_cast<std::size_t>(max))
                {
                    return;
                }
            }
        }
    }

    void entityfinder_register(lua_State* L)
    {
        lua_newtable(L);
        create_metatable(L,
            {
                { "__call", entityfinder_call }
            });
        lua_setglobal(L, "EntityFinder");
    }
}
