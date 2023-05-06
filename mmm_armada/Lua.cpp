#include "Lua.h"

namespace mmm
{
    namespace lua
    {
        void set_metatable(lua_State* L, int index, lua_CFunction index_function, lua_CFunction newindex_function, lua_CFunction gc_function)
        {
            const int actual_index = index < 0 ? lua_gettop(L) + index + 1 : index;
            lua_newtable(L);
            lua_pushcfunction(L, index_function);
            lua_setfield(L, -2, "__index");
            lua_pushcfunction(L, newindex_function);
            lua_setfield(L, -2, "__newindex");
            lua_pushcfunction(L, gc_function);
            lua_setfield(L, -2, "__gc");
            lua_setmetatable(L, actual_index);
        }

        void add_function(lua_State* L, int index, lua_CFunction function, const std::string& name)
        {
            const int actual_index = index < 0 ? lua_gettop(L) + index + 1 : index;
            lua_pushcfunction(L, function);
            lua_setfield(L, actual_index, name.c_str());
        }

        void set_integer(lua_State* L, int index, const std::string& name, int value)
        {
            if (index < 0)
            {
                index += lua_gettop(L) + 1;
            }
            lua_pushinteger(L, value);
            lua_setfield(L, index, name.c_str());
        }

        void create_enum(lua_State* L, const std::vector<EnumValue>& values)
        {
            lua_newtable(L);
            for (const auto& v : values)
            {
                set_integer(L, -1, v.name.c_str(), v.value);
            }
        }

        void set_enum(lua_State* L, const std::string& name, int index, const std::vector<EnumValue>& values)
        {
            if (index < 0)
            {
                index += lua_gettop(L) + 1;
            }

            create_enum(L, values);
            lua_setfield(L, index, name.c_str());
        }
    }
}
