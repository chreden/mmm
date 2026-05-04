#include "EntityFinderFilterObject.h"
#include "Entity_Internal.h"
#include "ScriptErrors.h"
#include <format>

namespace mmm
{
    EntityFinderFilterObject::EntityFinderFilterObject(lua_State* L, int table, int function)
        : _L(L), _table(table), _function(function)
    {
    }

    EntityFinderFilterObject::~EntityFinderFilterObject()
    {
        luaL_unref(_L, LUA_REGISTRYINDEX, _table);
        luaL_unref(_L, LUA_REGISTRYINDEX, _function);
    }

    bool EntityFinderFilterObject::call(const std::shared_ptr<Entity>& entity)
    {
        lua_rawgeti(_L, LUA_REGISTRYINDEX, _function);
        lua_rawgeti(_L, LUA_REGISTRYINDEX, _table);
        entity_new(_L, entity);
        if (LUA_OK != lua_pcall(_L, 2, 1, 0))
        {
            scriptError(std::format("Error in Filter Function: {}", lua_tostring(_L, -1)));
            return false;
        }
        bool result = lua_toboolean(_L, -1);
        lua_pop(_L, 1);
        return result;
    }
}
