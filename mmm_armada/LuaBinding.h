#pragma once

#include <lua.hpp>

#include <unordered_map>
#include <string>

namespace mmm
{
    void initLua();
    void shutdownLua();
    void registerTypes();

    void assign_metatable(lua_State* L, int ref_index);
    // Compare whether the item at the specified stack index has a metatable
    // equal to the one in the registry.
    bool equal_metatable(lua_State* L, int stack_index, int ref_index);
    void create_enum(lua_State* L, const std::string& name, const std::vector<std::tuple<std::string, int>>& values);
    int store_metatable(lua_State* L, const std::unordered_map<std::string, lua_CFunction>& map);
    void create_metatable(lua_State* L, const std::unordered_map<std::string, lua_CFunction>& map);

    template <typename T>
    void create_userdata(lua_State* L, const T& value);
    template <typename T>
    void cleanup_userdata(lua_State* L, int index = 1);
    template <typename T>
    T& get_userdata(lua_State* L, int index);
}

#include "LuaBinding.inl"
