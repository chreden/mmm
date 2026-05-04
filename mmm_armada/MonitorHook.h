#pragma once

#include "Hook.h"

namespace mmm
{
    class MonitorHook final : public Hook
    {
    public:
        enum Type
        {
            OnTrue = 0,
            OnFalse,
            WhileTrue,
            WhileFalse,
            OnStop
        };

        explicit MonitorHook(const std::string& id, int table, int function, int argument, Type type);
        Type getType() const;
        void setType(Type type);

        int index(lua_State* L, const std::string& key) const override;
        int newindex(lua_State* L, const std::string& key) override;
    private:
        Type _type;
    };

    void monitorhook_register(lua_State* L);
}
