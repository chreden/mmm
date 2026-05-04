#include "Hook.h"
#include "LuaBinding.h"

namespace mmm
{
    namespace
    {
        int hook_metatable{ LUA_NOREF };

        int hook_index(lua_State* L)
        {
            auto self = get_userdata<std::shared_ptr<Hook>>(L, 1);
            std::string key = lua_tostring(L, 2);
            return self->index(L, key);
        }

        int hook_newindex(lua_State* L)
        {
            auto self = get_userdata<std::shared_ptr<Hook>>(L, 1);
            std::string key = lua_tostring(L, 2);
            return self->newindex(L, key);
        }

        int hook_gc(lua_State* L)
        {
            cleanup_userdata<std::shared_ptr<Hook>>(L);
            return 0;
        }
    }

    Hook::~Hook()
    {
        lua_State* L = common::Storage::instance().mainLuaVM;
        luaL_unref(L, LUA_REGISTRYINDEX, _argument);
        luaL_unref(L, LUA_REGISTRYINDEX, _function);
        luaL_unref(L, LUA_REGISTRYINDEX, _table);
    }

    int Hook::index(lua_State* L, const std::string& key) const
    {
        if (key == "id")
        {
            lua_pushstring(L, id().c_str());
            return 1;
        }
        else if (key == "argument")
        {
            lua_rawgeti(L, LUA_REGISTRYINDEX, argument());
            return 1;
        }
        return 0;
    }

    int Hook::newindex(lua_State* L, const std::string& key)
    {
        if (key == "argument")
        {
            int argument = luaL_ref(L, LUA_REGISTRYINDEX);
            set_argument(argument);
        }
        return 0;
    }

    Hook::Hook(const std::string& id, int table, int function, int argument)
        : _id(id), _table(table), _function(function), _argument(argument)
    {
    }

    std::string Hook::id() const
    {
        return _id;
    }

    int Hook::argument() const
    {
        return _argument;
    }

    int Hook::table() const
    {
        return _table;
    }

    int Hook::function() const
    {
        return _function;
    }

    void Hook::set_argument(int argument)
    {
        _argument = argument;
    }

    int hook_new(lua_State* L, const std::shared_ptr<Hook>& hook)
    {
        create_userdata(L, hook);
        assign_metatable(L, hook_metatable);
        return 1;
    }

    void hook_register(lua_State* L)
    {
        hook_metatable = store_metatable(L,
            {
                { "__index", hook_index },
                { "__newindex", hook_newindex },
                { "__gc", hook_gc }
            });
    }
}
