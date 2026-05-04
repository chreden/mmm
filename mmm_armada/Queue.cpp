#include "Queue.h"
#include "QueueType.h"
#include "Entity_Internal.h"
#include "Type_Craft.h"
#include "LuaBinding.h"

namespace mmm
{
    namespace
    {
        const std::size_t Function_Remove = 0x00537800;

        int queue_metatable{ LUA_NOREF };

        int queue_index(lua_State* L)
        {
            const auto self = get_userdata<std::shared_ptr<Queue>>(L, 1);
            const std::string key = lua_tostring(L, 2);
            return self->index(L, key);
        }

        int queue_newindex(lua_State* L)
        {
            auto self = get_userdata<std::shared_ptr<Queue>>(L, 1);
            const std::string key = lua_tostring(L, 2);
            return self->newindex(L, key);
        }
    }

    Queue::Queue(types::Queue* queue)
        : queue_(queue)
    {
    }

    types::Queue* Queue::getQueue() const
    {
        return queue_;
    }

    int Queue::getSize() const
    {
        return queue_->m_idList.size();
    }

    int Queue::getEntries(lua_State* L) const
    {
        lua_newtable(L);
        for (int i = 0; i < queue_->m_idList.size(); ++i)
        {
            entity_new(L, createEntityPtr(GetEntity<types::Entity>(queue_->m_idList.at(i))));
            lua_rawseti(L, -2, i + 1);
        }
        return 1;
    }

    Vector3 Queue::getOffset() const
    {
        return queue_->m_offset;
    }

    //?remove@QueueManager@@QAEXPAVCraft@@@Z 00537800
    //thiscall void QueueManager::remove(types::Craft* craft) @ 0x00537800

    void Queue::remove(const std::shared_ptr<Entity>& entity)
    {
        if(entity->isType(Entity_Craft))
        {
            types::Craft* craft = static_cast<types::Craft*>(entity->getEntity());
            (getQueue()->*memory_function<void (types::Queue::*)(types::Craft*)>(Function_Remove))
                (craft);
        }
    }

    int Queue::index(lua_State* L, const std::string& key) const
    {
        if (key == "entries")
        {
            return getEntries(L);
        }
        else if (key == "size")
        {
            lua_pushnumber(L, getSize());
            return 1;
        }
        else if (key == "offset")
        {
            return vector_new(L, getOffset());
        }
        return 0;
    }

    int Queue::newindex(lua_State* L, const std::string& key)
    {
        return 0;
    }

    int queue_new(lua_State* L, const std::shared_ptr<Queue>& queue)
    {
        create_userdata(L, queue);
        assign_metatable(L, queue_metatable);
        return 1;
    }

    void queue_register(lua_State* L)
    {
        queue_metatable = store_metatable(L,
            {
                { "__index", queue_index },
                { "__newindex", queue_newindex }
            });
    }
}
