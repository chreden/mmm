#pragma once

#include "Craft_Internal.h"

namespace mmm
{
    namespace types { class Producer; }

    class Producer : public Craft
    {
    public:
        static ProducerPtr create(types::Entity* entity);
        std::shared_ptr<Entity> getLastBuilt() const;
        BuildQueuePtr getBuildQueue() const;
        float getBuildObjectTime() const;
        types::Producer* getProducer() const;
        int index(lua_State* L, const std::string& key) const override;
    protected:
        explicit Producer(types::Producer* producer);
    };
}
