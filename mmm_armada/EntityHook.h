#pragma once

#include "Hook.h"

namespace mmm
{
    class EntityHook final : public Hook
    {
    public:
        enum Type
        {
            OnDestroy,
            OnReplace
        };

        /**
            Create a new EntityHook.
            @param id The id for the new hook.
            @param table The table for the hook function.
            @param function The function to call.
            @param argument The argument to store in the hook.
            @param type The Entity hook type
        */
        explicit EntityHook(const std::string& id, Type type, int table, int function, int argument );
        Type getType() const;
        void setType(Type type);

        int index(lua_State* L, const std::string& key) const override;
        int newindex(lua_State* L, const std::string& key) override;
    private:
        Type type_;
    };

    int entityhook_new(lua_State* L, const std::shared_ptr<EntityHook>& hook);
    void entityhook_register(lua_State* state);
}
