#include "Producer.h"
#include "Type_Producer.h"
#include "Type_Entity.h"
#include "GameObject_Internal.h"
#include "ProducerClass_Internal.h"
#include "Type_ProducerClass.h"
#include "Type_ResearchStation.h"
#include "BuildQueue.h"

namespace mmm
{
    namespace
    {
        const std::size_t Address_GetBuildObjectTime = 0x004b7cd0;
    }

    std::shared_ptr<Producer> Producer::create(types::Entity* entity)
    {
        return std::shared_ptr<Producer>(new Producer(static_cast<types::Producer*>(entity)));
    }

    Producer::Producer(types::Producer* producer)
        : Craft(producer)
    {

    }

    types::Producer* Producer::getProducer() const
    {
        return static_cast<types::Producer*>(getEntity());
    }

    std::shared_ptr<BuildQueue> Producer::getBuildQueue() const
    {
        return BuildQueue::create(std::static_pointer_cast<Producer>(std::const_pointer_cast<Entity>(shared_from_this())));
    }

    std::shared_ptr<Entity> Producer::getLastBuilt() const
    {
        return createEntityPtr(GetEntity<types::Entity>(getProducer()->m_previousShipBuilt));
    } 

    float Producer::getBuildObjectTime() const
    {
        typedef float (types::Producer::*MemFunction) ();
        MemFunction function = memory_function< MemFunction >(Address_GetBuildObjectTime);
        return (getProducer()->*function)();
    }

    int Producer::index(lua_State* L, const std::string& key) const
    {
        if (key == "buildObjectTime")
        {
            lua_pushnumber(L, getBuildObjectTime());
            return 1;
        }
        else if (key == "buildQueue")
        {
            return buildqueue_new(L, getBuildQueue());
        }
        else if (key == "lastBuilt")
        {
            return entity_new(L, getLastBuilt());
        }
        return Craft::index(L, key);
    }
}
