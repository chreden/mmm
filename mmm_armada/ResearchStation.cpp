#include "ResearchStation.h"
#include "Type_ResearchStation.h"

namespace mmm
{
    ResearchStationPtr ResearchStation::create(types::Entity* entity)
    {
        return ResearchStationPtr(new ResearchStation(static_cast<types::ResearchStation*>(entity)));
    }

    ResearchStation::ResearchStation(types::ResearchStation* station)
        : Producer(station)
    {

    }

    types::ResearchStation* ResearchStation::getResearchStation() const
    {
        return static_cast<types::ResearchStation*>(getEntity());
    }

    int ResearchStation::getPods(lua_State* L) const
    {
        lua_newtable(L);
        const types::ResearchStation* const station = getResearchStation();
        for (int i = 0; i < station->m_numberOfPods; ++i)
        {
            entity_new(L, createEntityPtr(station->m_ppPods[i]));
            lua_rawseti(L, -2, i + 1);
        }
        return 1;
    }

    int ResearchStation::index(lua_State* L, const std::string& key) const
    {
        if (key == "pods")
        {
            return getPods(L);
        }
        return Producer::index(L, key);
    }
}
