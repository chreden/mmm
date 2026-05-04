#include "Monitor.h"
#include "ScriptErrors.h"
#include "MonitorHook.h"
#include "LuaBinding.h"

namespace mmm
{
    namespace
    {
        std::vector<std::shared_ptr<Monitor>> monitors_;
        int monitor_metatable{ LUA_NOREF };

        int monitor_class_find(lua_State* L)
        {
            std::string id = lua_tostring(L, 1);
            monitor_new(L, Monitor::find(id));
            return 1;
        }

        int monitor_class_get_all(lua_State* L)
        {
            return Monitor::getAll(L);
        }

        int monitor_class_stop_all(lua_State* L)
        {
            Monitor::stopAll();
            return 0;
        }

        int monitor_class_index(lua_State* L)
        {
            const std::string key = lua_tostring(L, 2);

            if (key == "find")
            {
                lua_pushcfunction(L, monitor_class_find);
                return 1;
            }
            else if (key == "getAll")
            {
                lua_pushcfunction(L, monitor_class_get_all);
                return 1;
            }
            else if (key == "stopAll")
            {
                lua_pushcfunction(L, monitor_class_stop_all);
                return 1;
            }

            return 0;
        }

        int monitor_hook(lua_State* L)
        {
            auto self = get_userdata<std::shared_ptr<Monitor>>(L, 1);
            std::string id = lua_tostring(L, 2);
            MonitorHook::Type type = static_cast<MonitorHook::Type>(lua_tointeger(L, 3));
            int arg = luaL_ref(L, LUA_REGISTRYINDEX);
            int function = luaL_ref(L, LUA_REGISTRYINDEX);
            int table = luaL_ref(L, LUA_REGISTRYINDEX);
            self->addHook(id, type, table, function, arg);
            return 0;
        }

        int monitor_stop(lua_State* L)
        {
            const auto self = get_userdata<std::shared_ptr<Monitor>>(L, 1);
            self->stop();
            return 0;
        }

        int monitor_unhook(lua_State* L)
        {
            const auto self = get_userdata<std::shared_ptr<Monitor>>(L, 1);
            if (lua_type(L, 2) == LUA_TSTRING)
            {
                self->unhook(lua_tostring(L, 2));
            }
            else if (lua_type(L, 2) == LUA_TUSERDATA)
            {
                self->unhook(get_userdata<std::shared_ptr<MonitorHook>>(L, 2));
            }
            return 0;
        }

        int monitor_index(lua_State* L)
        {
            const auto self = get_userdata<std::shared_ptr<Monitor>>(L, 1);
            const std::string key = lua_tostring(L, 2);

            if (key == "hook")
            {
                lua_pushcfunction(L, monitor_hook);
                return 1;
            }
            else if (key == "hooks")
            {
                return self->getHooks();
            }
            else if (key == "id")
            {
                lua_pushstring(L, self->getID().c_str());
                return 1;
            }
            else if (key == "state")
            {
                lua_pushboolean(L, self->getState());
                return 1;
            }
            else if (key == "stop")
            {
                lua_pushcfunction(L, monitor_stop);
                return 1;
            }
            else if (key == "unhook")
            {
                lua_pushcfunction(L, monitor_unhook);
                return 1;
            }

            return 0;
        }

        int monitor_gc(lua_State* L)
        {
            cleanup_userdata<std::shared_ptr<Monitor>>(L);
            return 0;
        }

        int monitor_call(lua_State* L)
        {
            std::string id = lua_tostring(L, 2);
            bool initialState = lua_toboolean(L, 3);
            int arg = luaL_ref(L, LUA_REGISTRYINDEX);
            int function = luaL_ref(L, LUA_REGISTRYINDEX);
            int table = luaL_ref(L, LUA_REGISTRYINDEX);
            auto monitor_ptr = Monitor::add(L, id, initialState, table, function, arg);
            create_userdata(L, monitor_ptr);
            create_metatable(L,
                {
                    { "__index", monitor_index },
                    { "__gc", monitor_gc }
                });
            return 1;
        }
    }

    Monitor::Monitor(lua_State* L, const std::string& id, bool initialState, int conditionTable, int conditionFunction, int conditionArgument)
        : _L(L), _id(id), _conditionTable(conditionTable), _conditionFunction(conditionFunction), _conditionArgument(conditionArgument), _state(initialState)
    {
    }

    std::shared_ptr<Monitor> Monitor::add(lua_State* L, const std::string& id, bool initialState, int conditionTable, int conditionFunction, int conditionArgument)
    {
        auto monitor = std::make_shared<Monitor>(L, id, initialState, conditionTable, conditionFunction, conditionArgument);
        monitors_.push_back(monitor);
        return monitor;
    }

    std::string Monitor::getID() const
    {
        return _id;
    }

    bool Monitor::addHook(const std::string& id, MonitorHook::Type type, int table, int function, int argument)
    {
        //Search through the hooks to see if we already have something with this id.
        if(_hooks.find(id) != _hooks.end())
        {
            return false;
        }
        _hooks[id] = std::make_shared<MonitorHook>(id, table, function, argument, type);
        return true;
    }

    bool Monitor::unhook(const std::string& id)
    {
        auto iter = _hooks.find(id);
        if(iter == _hooks.end())
        {
            return false;
        }
        _hooks.erase(iter);
        return true;
    }

    bool Monitor::unhook(const std::shared_ptr<Hook>& hook)
    {
        auto iter = std::find_if(_hooks.begin(), _hooks.end(),
                    [&](const std::pair<std::string, std::shared_ptr<MonitorHook>>& hookIter)
                        {
                            return hookIter.second == hook;
                        });
        if(iter == _hooks.end())
        {
            return false;
        }
        _hooks.erase(iter);
        return true;
    }

    int Monitor::getHooks() const
    {
        lua_newtable(_L);
        for (const auto& hook : _hooks)
        {
            hook_new(_L, hook.second);
            lua_setfield(_L, -2, hook.first.c_str());
        }
        return 1;
    }

    void Monitor::testAndFire()
    {
        bool newState = test();
        MonitorHook::Type hookType = selectHook(newState);
        setState(newState);
        callHook(hookType);
    }

    bool Monitor::test()
    {
        lua_rawgeti(_L, LUA_REGISTRYINDEX, _conditionTable);
        if (lua_type(_L, -1) == LUA_TTABLE)
        {
            lua_rawgeti(_L, LUA_REGISTRYINDEX, _conditionFunction);
            lua_pushvalue(_L, -2);
            monitor_new(_L, shared_from_this());
            lua_rawgeti(_L, LUA_REGISTRYINDEX, _conditionArgument);
            if (LUA_OK != lua_pcall(_L, 3, 1, 0))
            {
                scriptError(std::string("Error in monitor condition function : ") + lua_tostring(_L, -1));
                return false;
            }
        }
        else
        {
            lua_rawgeti(_L, LUA_REGISTRYINDEX, _conditionFunction);
            monitor_new(_L, shared_from_this());
            lua_rawgeti(_L, LUA_REGISTRYINDEX, _conditionArgument);
            if (LUA_OK != lua_pcall(_L, 2, 1, 0))
            {
                scriptError(std::string("Error in monitor condition function : ") + lua_tostring(_L, -1));
                return false;
            }
        }
        return lua_toboolean(_L, -1);
    }

    MonitorHook::Type Monitor::selectHook(bool newValue) const
    {
        if(newValue == _state)
        {
            if(_state)
            {
                return MonitorHook::WhileTrue;
            }
            else
            {
                return MonitorHook::WhileFalse;
            }
        }

        if(newValue)
        {
            return MonitorHook::OnTrue;
        }
        return MonitorHook::OnFalse;
    }

    void Monitor::stop()
    {
        //Inform listeners that we are about to be destroyed.
        callHook(MonitorHook::OnStop);

        //Actually proceed with the destruction of ourself.
        auto iter = std::find(monitors_.begin(), monitors_.end(), shared_from_this());
        if (iter != monitors_.end())
        {
            monitors_.erase(iter);
        }
    }

    bool Monitor::getState() const
    {
        return _state;
    }

    void Monitor::setState(bool value)
    {
        _state = value;
    }

    void Monitor::callHook(MonitorHook::Type hookType)
    {
        //Similar to updating the monitors, we take a copy of the hooks
        //here so they can be removed during updating.
        auto hooksCopy = _hooks;
        for (const auto& hook : hooksCopy)
        {
            const auto ptr = hook.second;
            if (ptr && ptr->getType() == hookType)
            {
                lua_rawgeti(_L, LUA_REGISTRYINDEX, ptr->table());
                if (lua_type(_L, -1) == LUA_TTABLE)
                {
                    lua_rawgeti(_L, LUA_REGISTRYINDEX, ptr->function());
                    lua_pushvalue(_L, -2);
                    monitor_new(_L, shared_from_this());
                    hook_new(_L, ptr);
                    if (LUA_OK != lua_pcall(_L, 3, 0, 0))
                    {
                        scriptError(std::string("Error in Monitor Hook (" + _id + "):(" + ptr->id() + ") : ") + lua_tostring(_L, -1));
                    }
                }
                else
                {
                    lua_rawgeti(_L, LUA_REGISTRYINDEX, ptr->function());
                    monitor_new(_L, shared_from_this());
                    hook_new(_L, ptr);
                    if (LUA_OK != lua_pcall(_L, 2, 0, 0))
                    {
                        scriptError(std::string("Error in Monitor Hook (" + _id + "):(" + ptr->id() + ") : ") + lua_tostring(_L, -1));
                    }
                }
            }
        }
    }

    void Monitor::update()
    {
        const auto monitors = monitors_;
        for( std::size_t i = 0; i < monitors.size(); ++i )
        {
            monitors[i]->testAndFire();
        }
    }

    std::shared_ptr<Monitor> Monitor::find(const std::string& id)
    {
        const std::size_t Count = monitors_.size();
        for( std::size_t i = 0; i < Count; ++i )
        {
            if (monitors_[i]->getID() == id)
            {
                return monitors_[i];
            }
        }
        return {};
    }

    int Monitor::getAll(lua_State* L)
    {
        lua_newtable(L);
        const std::size_t Count = monitors_.size();
        for (std::size_t i = 0; i < Count; ++i)
        {
            monitor_new(L, monitors_[i]);
            lua_rawseti(L, -2, i + 1);
        }
        return 1;
    }

    void Monitor::clear()
    {
        monitors_.clear();
    }

    void Monitor::stopAll()
    {
        const auto monitors = monitors_;
        for (const auto& monitor : monitors)
        {
            monitor->stop();
        }
    }

    int monitor_new(lua_State* L, const std::shared_ptr<Monitor>& monitor)
    {
        if (!monitor)
        {
            lua_pushnil(L);
            return 1;
        }

        create_userdata(L, monitor);
        assign_metatable(L, monitor_metatable);
        return 1;
    }

    void monitor_register(lua_State* L)
    {
        lua_newtable(L);
        create_metatable(L,
            {
                { "__index", monitor_class_index },
                { "__call", monitor_call }
            });
        create_enum(L, "Relation",
            {
                { "Enemy", TEAM_ENEMY },
                { "Neutral", TEAM_NEUTRAL },
                { "Ally", TEAM_ALLY }
            });
        lua_setglobal(L, "Monitor");

        monitor_metatable = store_metatable(L,
            {
                { "__index", monitor_index },
                { "__gc", monitor_gc }
            });
    }
}
