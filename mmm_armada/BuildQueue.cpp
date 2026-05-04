#include "BuildQueue.h"
#include "Type_Producer.h"
#include "GameObjectClass_Internal.h"
#include "LuaBinding.h"

namespace mmm
{
    namespace
    {
        const std::size_t Address_ClearBuildQueue = 0x004b78c0;
        const std::size_t Address_PushBuildQueueItem = 0x004b7930;
        const std::size_t Address_PopBuildQueueItem = 0x004b79b0;
        const std::size_t Address_IsBuildListEmpty = 0x004b7b60;
        const std::size_t Address_GetBuildQueueSize = 0x004b7b70;
        const std::size_t Address_StartBuild = 0x004b8180;
        const std::size_t Address_RemoveItem = 0x004b7a10;
        int buildqueue_metatable{ LUA_NOREF };

        void producer_clearBuildQueue(types::Producer* producer)
        {
            (producer->*memory_function< void (types::Producer::*) () >(Address_ClearBuildQueue))();
        }

        bool producer_pushBuildQueue(types::Producer* producer, const std::string& odf)
        {
            GameObjectClass* gameClass = static_cast<GameObjectClass*>(FindGameObjectClass(odf.c_str()));
            if(gameClass)
            {
                (producer->*memory_function<void (types::Producer::*)(GameObjectClass*)>(Address_PushBuildQueueItem))(gameClass);
                return true;
            }
            return false;
        }

        void producer_popBuildQueue(types::Producer* producer)
        {
            (producer->*memory_function<void (types::Producer::*)()>(Address_PopBuildQueueItem))();
        }

        bool producer_isBuildQueueEmpty(types::Producer* producer)
        {
            return (producer->*memory_function< bool (types::Producer::*)() >(Address_IsBuildListEmpty))();
        }

        int producer_getBuildQueueSize(types::Producer* producer)
        {
            return (producer->*memory_function< int (types::Producer::*)() >(Address_GetBuildQueueSize))();
        }

        void producer_completeBuildItem(types::Producer* producer)
        {
            if(!producer_isBuildQueueEmpty(producer))
            {
                producer->m_buildDoneTime = 0;
                (producer->*memory_function<bool (types::Producer::*)() >(Address_StartBuild))();
            }
        }

        void producer_removeBuildQueueItem(types::Producer* producer, int index)
        {
            (producer->*memory_function< void (types::Producer::*)(int) >(Address_RemoveItem))(index);
        }

        int buildqueue_clear(lua_State* L)
        {
            auto self = get_userdata<std::shared_ptr<BuildQueue>>(L, 1);
            self->clear();
            return 0;
        }

        int buildqueue_complete(lua_State* L)
        {
            auto self = get_userdata<std::shared_ptr<BuildQueue>>(L, 1);
            self->complete();
            return 0;
        }

        int buildqueue_pop(lua_State* L)
        {
            auto self = get_userdata<std::shared_ptr<BuildQueue>>(L, 1);
            self->pop();
            return 0;
        }

        int buildqueue_push(lua_State* L)
        {
            auto self = get_userdata<std::shared_ptr<BuildQueue>>(L, 1);
            self->push(lua_tostring(L, 2));
            return 0;
        }

        int buildqueue_remove(lua_State* L)
        {
            auto self = get_userdata<std::shared_ptr<BuildQueue>>(L, 1);
            self->remove(lua_tonumber(L, 2));
            return 0;
        }

        int buildqueue_index(lua_State* L)
        {
            auto self = get_userdata<std::shared_ptr<BuildQueue>>(L, 1);
            const std::string key = lua_tostring(L, 2);

            if (key == "clear")
            {
                lua_pushcfunction(L, buildqueue_clear);
                return 1;
            }
            else if (key == "complete")
            {
                lua_pushcfunction(L, buildqueue_complete);
                return 1;
            }
            else if (key == "empty")
            {
                lua_pushboolean(L, self->isEmpty());
                return 1;
            }
            else if (key == "items")
            {
                return self->getItems(L);
            }
            else if (key == "pop")
            {
                lua_pushcfunction(L, buildqueue_pop);
                return 1;
            }
            else if (key == "push")
            {
                lua_pushcfunction(L, buildqueue_push);
                return 1;
            }
            else if (key == "remove")
            {
                lua_pushcfunction(L, buildqueue_remove);
                return 1;
            }
            else if (key == "timeRemaining")
            {
                lua_pushnumber(L, self->getTimeRemaining());
                return 1;
            }
            return 0;
        }
    }

    BuildQueuePtr BuildQueue::create(ProducerPtr producer)
    {
        return BuildQueuePtr(new BuildQueue(producer));
    }

    BuildQueue::BuildQueue(ProducerPtr producer)
        : producer_(producer)
    {
    }

    void BuildQueue::clear()
    {
        producer_clearBuildQueue(producer_->getProducer());
    }

    bool BuildQueue::push(const std::string& odf)
    {
        return producer_pushBuildQueue(producer_->getProducer(), odf);
    }

    void BuildQueue::pop()
    {
        return producer_popBuildQueue(producer_->getProducer());
    }

    void BuildQueue::complete()
    {
        producer_completeBuildItem(producer_->getProducer());
    }

    int BuildQueue::getSize() const
    {
        return producer_getBuildQueueSize(producer_->getProducer());
    }

    int BuildQueue::getItems(lua_State* L) const
    {
        lua_newtable(L);
        types::BuildQueueItem* item = producer_->getProducer()->m_pBuildQueue;
        int i = 1;
        while (item)
        {
            gameobjectclass_new(L, createGameObjectClassPtr(item->m_next_obj));
            lua_rawseti(L, -2, i);
            i++;
            item = item->m_next;
        }
        return 1;
    }

    bool BuildQueue::isEmpty() const
    {
        return producer_isBuildQueueEmpty(producer_->getProducer());
    }

    void BuildQueue::remove(int index)
    {
        return producer_removeBuildQueueItem(producer_->getProducer(), index - 1);
    }

    float BuildQueue::getTimeRemaining() const
    {
        return producer_->getProducer()->m_buildDoneTime;
    }

    int buildqueue_new(lua_State* L, const std::shared_ptr<BuildQueue>& queue)
    {
        create_userdata(L, queue);
        assign_metatable(L, buildqueue_metatable);
        return 1;
    }

    void buildqueue_register(lua_State* L)
    {
        buildqueue_metatable = store_metatable(L,
            {
                { "__index", buildqueue_index },
            });
    }
}
