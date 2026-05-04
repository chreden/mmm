#pragma once

#include "Types.h"
#include "EntityHook.h"

namespace mmm
{
    namespace types
    {
        struct Entity;
    }

    struct EntityHook;

    class EntityReference
    {
    public:
        enum State
        {
            Inactive = 0,
            Active
        };

        static std::shared_ptr<EntityReference> create( int id );
        static std::shared_ptr<EntityReference> create( types::Entity* ent );
        ~EntityReference();
        State getState() const;
        types::Entity* getEntity() const;
        bool hasHooks() const;
        bool addHook(const std::string& id, EntityHook::Type type, int table, int function, int argument);
        bool unhook(const std::string& id);
        bool unhook(const std::shared_ptr<Hook>& hook);
        int getHooks(lua_State* L) const;
        void setID(int id);
        static void updateReferences();
        static void destroyReferences();
    private:
        static std::shared_ptr<EntityReference> find(int id);
        explicit EntityReference(int id);
        explicit EntityReference(types::Entity* ent);
        void callHook(EntityHook::Type type) const;
        void update();
        EntityID entityID_;
        State state_;
        std::unordered_map<std::string, std::shared_ptr<EntityHook>> hooks_;
    };
}
