#include "EntityFinderFilterFunction.h"
#include "Entity_Internal.h"
#include "ScriptErrors.h"
#include <format>

namespace mmm
{
    EntityFinderFilterFunction::EntityFinderFilterFunction(lua_State* L, int index)
        : _L(L), _index(index)
    {
    }

    EntityFinderFilterFunction::~EntityFinderFilterFunction()
    {
        luaL_unref(_L, LUA_REGISTRYINDEX, _index);
    }

    bool EntityFinderFilterFunction::call(const std::shared_ptr<Entity>& entity)
    {
        lua_rawgeti(_L, LUA_REGISTRYINDEX, _index);
        entity_new(_L, entity);
        if (LUA_OK != lua_pcall(_L, 1, 1, 0))
        {
            scriptError(std::format("Error in Filter Function: {}", lua_tostring(_L, -1)));
            return false;
        }
        bool result = lua_toboolean(_L, -1);
        lua_pop(_L, 1);
        return result;
    }
}
