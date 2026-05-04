#pragma once

#include <lua.hpp>
#include <string>
#include <unordered_map>

#include "MonitorHook.h"

namespace mmm
{
    /**
        A Monitor tracks the state of a condition by calling a user defined
        function. The user can attach hooks that will be called when the
        condition changes state.
    */
    class Monitor : public std::enable_shared_from_this<Monitor>
    {
    public:
        /**
            Add a hook to the monitor.
            @param id The unique identifier of the new hook.
            @param type The event to hook on to.
            @param table The table of the hook function.
            @param function The function to call.
            @param argument An argument for the function.
            @return True if the hook was created successfully.
        */
        bool addHook(const std::string& id, MonitorHook::Type type, int table, int function, int argument);
        /**
            Remove the specified hook from the monitor.
            @param id The id of the monitor to remove
        */
        bool unhook(const std::string& id);
        /**
            Remove the specified hook from the monitor.
            @param hook The hook to remove.
        */
        bool unhook(const std::shared_ptr<Hook>& hook);
        /**
            Stop the monitor. This will remove the monitor from the active
            monitors list.
        */
        void stop();
        /**
            Get the identifier of the Monitor.
            @return The id of the monitor.
        */
        std::string getID() const;
        /**
            Get the current state of the monitor's condition.
            @return The current condition state.
        */
        bool getState() const;
        /**
            Get all registered hooks.
            @return A table of registered hooks.
        */
        int getHooks() const;

        static std::shared_ptr<Monitor> add(lua_State* L, const std::string& id, bool initialState, int conditionTable, int conditionFunction, int conditionArgument);
        static void update();
        static std::shared_ptr<Monitor> find(const std::string& id);
        static int getAll(lua_State* L);
        static void clear();
        static void stopAll();
        Monitor(lua_State* L, const std::string& id, bool initialState, int conditionTable, int conditionFunction, int conditionArgument);
    private:
        bool test();
        MonitorHook::Type selectHook(bool newValue) const;
        void setState(bool value);
        void callHook(MonitorHook::Type hookType);
        void testAndFire();

        lua_State* _L;
        std::unordered_map<std::string, std::shared_ptr<MonitorHook>> _hooks;
        std::string _id;
        int _conditionTable;
        int _conditionFunction;
        int _conditionArgument;
        bool _state;
    };

    int monitor_new(lua_State* L, const std::shared_ptr<Monitor>& monitor);
    void monitor_register(lua_State* state);
}
