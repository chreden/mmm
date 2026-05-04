#include "MonitorHook.h"
#include "LuaBinding.h"

namespace mmm
{
    MonitorHook::MonitorHook(const std::string& id, int table, int function, int argument, Type type)
        : Hook(id, table, function, argument), _type(type)
    {
    }
    
    MonitorHook::Type MonitorHook::getType() const
    {
        return _type;
    }

    void MonitorHook::setType(Type type)
    {
        _type = type;
    }

    int MonitorHook::index(lua_State* L, const std::string& key) const
    {
        if (key == "hookType")
        {
            lua_pushnumber(L, getType());
            return 1;
        }
        return Hook::index(L, key);
    }

    int MonitorHook::newindex(lua_State* L, const std::string& key)
    {
        if (key == "hookType")
        {
            setType(static_cast<MonitorHook::Type>(lua_tonumber(L, 3)));
        }
        return Hook::newindex(L, key);
    }

    void monitorhook_register(lua_State* L)
    {
        lua_newtable(L);
        create_enum(L, "Type",
            {
                { "OnTrue", MonitorHook::OnTrue },
                { "OnFalse", MonitorHook::OnFalse },
                { "WhileTrue", MonitorHook::WhileTrue },
                { "WhileFalse", MonitorHook::WhileFalse },
                { "OnStop", MonitorHook::OnStop }
            });
        lua_setglobal(L, "MonitorHook");
    }
}
