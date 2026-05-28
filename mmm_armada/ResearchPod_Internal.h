#pragma once

#include "Craft_Internal.h"

namespace mmm
{
    namespace types { struct ResearchPod; }

    class ResearchPod : public Craft
    {
    public:
        static std::shared_ptr<ResearchPod> create(types::Entity* entity);
        std::shared_ptr<Entity> getStation() const;
        int index(lua_State* L, const std::string& key) const override;
    protected:
        explicit	 ResearchPod(types::ResearchPod* pod);
    private:
        types::ResearchPod* getResearchPod() const;
    };
}

