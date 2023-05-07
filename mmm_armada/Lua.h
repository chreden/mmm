#pragma once

namespace mmm
{
    namespace lua
    {
        struct EnumValue
        {
            std::string name;
            int value;
        };

        void set_metatable(lua_State* L, int index, lua_CFunction index_function, lua_CFunction newindex_function, lua_CFunction gc_function);
        void add_function(lua_State* L, int index, lua_CFunction function, const std::string& name);
        void set_integer(lua_State* L, int index, const std::string& name, int value);
        void create_enum(lua_State* L, const std::vector<EnumValue>& values);
        void set_enum(lua_State* L, const std::string& name, int index, const std::vector<EnumValue>& values);

        template <typename T>
        inline T* get_self(lua_State* L)
        {
            luaL_checktype(L, 1, LUA_TUSERDATA);
            return *static_cast<T**>(lua_touserdata(L, 1));
        }
    };
}
