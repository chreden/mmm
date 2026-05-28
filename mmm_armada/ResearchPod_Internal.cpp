#include "ResearchPod_Internal.h"
#include "Craft_Internal.h"
#include "Type_ResearchPod.h"
#include "Type_ResearchStation.h"

namespace mmm
{
    std::shared_ptr<ResearchPod> ResearchPod::create(types::Entity* entity)
    {
        return std::shared_ptr<ResearchPod>(new ResearchPod(static_cast<types::ResearchPod*>(entity)));
    }

    ResearchPod::ResearchPod(types::ResearchPod* pod)
        : Craft(pod)
    {

    }

    std::shared_ptr<Entity> ResearchPod::getStation() const
    {
        return createEntityPtr(getResearchPod()->researchStation);
    }

    types::ResearchPod* ResearchPod::getResearchPod() const
    {
        return static_cast<types::ResearchPod*>(getEntity());
    }

    int ResearchPod::index(lua_State* L, const std::string& key) const
    {
        if (key == "station")
        {
            return entity_new(L, getStation());
        }
        return Craft::index(L, key);
    }
}
