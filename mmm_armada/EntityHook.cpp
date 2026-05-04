#include "EntityHook.h"
#include "LuaBinding.h"

namespace mmm
{
    EntityHook::EntityHook( const std::string& id, Type type, int table, int function, int argument )
        : Hook(id, table, function, argument), type_(type)
    {
    }

    EntityHook::Type EntityHook::getType() const
    {
        return type_;
    }

    void EntityHook::setType(Type type)
    {
        type_ = type;
    }

    int EntityHook::index(lua_State* L, const std::string& key) const
    {
        if (key == "hookType")
        {
            lua_pushnumber(L, getType());
            return 1;
        }
        return Hook::index(L, key);
    }

    int EntityHook::newindex(lua_State* L, const std::string& key)
    {
        if (key == "hookType")
        {
            setType(static_cast<EntityHook::Type>(lua_tonumber(L, 3)));
        }
        return Hook::newindex(L, key);
    }

    void entityhook_register(lua_State* L)
    {
        lua_newtable(L);
        create_enum(L, "Type",
            {
                { "OnDestroy", EntityHook::OnDestroy },
                { "OnReplace", EntityHook::OnReplace }
            });
        lua_setglobal(L, "EntityHook");
    }
}

