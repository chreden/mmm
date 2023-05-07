#pragma once

namespace mmm
{
    namespace types { class Team; }

    enum eTradeDirection
    {
        TradeDir_To = 0,
        TradeDir_From
    };

    class Race;
    class Team
        : private NoCopy
    {
    public:
        explicit      Team(int teamNumber);
        explicit      Team(types::Team* team);
        eTeamRelation getRelation(const std::shared_ptr<Team>& other) const;
        int	          getMaxOfficers() const;
        float         getMaxCrew() const;
        void          getEntities(std::vector<EntityPtr>& out) const;
        ST3D_Colour   getColor() const;
        int           getNumber() const;
        float         getAmountTraded(eResource resource, eTradeDirection direction, const std::shared_ptr<Team>& other) const;
        eSlotType     getSlotType() const;
        std::shared_ptr<Race> getRace() const;
        bool          getIsAI() const;
        void          setColor(const ST3D_Colour& color);
        void          setRelation(const std::shared_ptr<Team>& other, eTeamRelation relation);
        void          setMaxOfficers(int value);
        void          setMaxCrew(float value);
        void          setIsAI(bool value);
        void          loadAIP(const std::string& aip);
        std::string   getName() const;
        void          setName(const std::string& name);
        bool          isValid() const;

        class Resources;
        std::shared_ptr<Resources> getResources() const;
    private:
        types::Team* _team{ nullptr };
        std::shared_ptr<Resources> _resources;
    };

    void team_register(lua_State* L);
    int team_create(lua_State* L, const std::shared_ptr<Team>& team);
    std::shared_ptr<Team> to_team(lua_State* L, int index);
}

#include "Team_Resources.h"