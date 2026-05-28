#pragma once

#include "Craft_Internal.h"

namespace mmm
{
    namespace types { class Producer; }

    class BuildQueue;
    class Producer : public Craft
    {
    public:
        static std::shared_ptr<Producer> create(types::Entity* entity);
        std::shared_ptr<Entity> getLastBuilt() const;
        std::shared_ptr<BuildQueue> getBuildQueue() const;
        float getBuildObjectTime() const;
        types::Producer* getProducer() const;
        int index(lua_State* L, const std::string& key) const override;
    protected:
        explicit Producer(types::Producer* producer);
    };
}
