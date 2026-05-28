#pragma once

namespace mmm
{
    namespace types { class Team; }

    enum eTradeDirection
    {
        TradeDir_To = 0,
        TradeDir_From
    };

    class Entity;
    class Race;
    class Team
    {
    public:
        explicit Team(int teamNumber);
        explicit Team(types::Team* team);
        Team(const Team& other) = delete;
        Team& operator=(const Team& other) = delete;
        float getResource(eResource resource) const;
        eTeamRelation getRelation(const std::shared_ptr<Team>& other) const;
        int getMaxOfficers() const;
        float getMaxCrew() const;
        void getEntities(std::vector<std::shared_ptr<Entity>>& out) const;
        ST3D_Colour getColor() const;
        int getNumber() const;
        float getAmountTraded(eResource resource, eTradeDirection direction, const std::shared_ptr<Team>& other) const;
        eSlotType getSlotType() const;
        std::shared_ptr<Race> getRace() const;
        bool getIsAI() const;
        bool getUseWormholes() const;
        void setColor(const ST3D_Colour& color);
        void setResource(eResource resource, float amount, bool relative);
        void setRelation(const std::shared_ptr<Team>& other, eTeamRelation relation);
        void setMaxOfficers(int value);
        void setMaxCrew(float value);
        void setIsAI(bool value);
        void loadAIP(const std::string& aip);
        const std::string getName() const;
        void setName(const std::string& name);
        void setRace(const std::shared_ptr<Race>& race);
        void setUseWormholes(bool value);
        bool isValid() const;
        class Resources;
        typedef std::shared_ptr<Resources> ResourcesPtr;
        ResourcesPtr getResources() const;
    private:
        types::Team* team_;
        //The resources class simply forwards things on.
        ResourcesPtr resources_;
    };

    int team_new(lua_State* L, const std::shared_ptr<Team>& team);
    void team_register(lua_State* L);
}

#include "Team_Resources.h"
