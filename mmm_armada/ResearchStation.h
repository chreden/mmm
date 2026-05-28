#pragma once

#include "Producer.h"

namespace mmm
{
    namespace types { struct ResearchStation; }

    class ResearchStation : public Producer
    {
    public:
        static std::shared_ptr<ResearchStation> create(types::Entity* entity);
        int getPods(lua_State* L) const;
        int index(lua_State* L, const std::string& key) const override;
    protected:
        explicit ResearchStation(types::ResearchStation* station);
    private:
        types::ResearchStation* getResearchStation() const;
    };
}
