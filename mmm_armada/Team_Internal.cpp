#include "Team_Internal.h"
#include "Type_Team.h"
#include "Type_Entity.h"
#include "Type_GameObject.h"
#include "Type_AI.h"

#include "Race_Internal.h"
#include "Entity_Internal.h"
#include "GameObject_Internal.h"
#include "Entities_Internal.h"

namespace mmm
{
    namespace
    {
        constexpr std::size_t Address_SetRelation = 0x004971d0;
        constexpr std::size_t Address_GetTeam = 0x00496340;
        constexpr std::size_t Address_GTransport = 0x0076b8d4;
        constexpr std::size_t Address_GetGameSetup = 0x00557930;
        constexpr std::size_t Address_Ais = 0x00735bc4;

        bool entIsTeam(EntityPtr ent, void* arguments)
        {
            return ent &&
                ent->isType(Entity_GameObject) &&
                boost::static_pointer_cast<GameObject>(ent)->getTeam()->getNumber() == reinterpret_cast<int>(arguments);
        }
    }

    Team::Team(int number)
    {
        typedef types::Team& (*MemFunction)(int);
        MemFunction function = memory_function<MemFunction>(Address_GetTeam);
        _team = &function(number);
        _resources = std::make_shared<Resources>(_team);
    }

    Team::Team(types::Team* team)
        : _team(team), _resources(std::make_shared<Resources>(team))
    {

    }

    eTeamRelation Team::getRelation(const std::shared_ptr<Team>& other) const
    {
        return _team->m_relationship[other->getNumber()];
    }

    void Team::setRelation(const std::shared_ptr<Team>& other, eTeamRelation relation)
    {
        //Ok, so setting manually and setting relations with script interface didn't actually
        //work, so I guess this is the only way to do it. It works fine though.
        _team->m_relationship[other->getNumber()] = relation;
        other->_team->m_relationship[getNumber()] = relation;
    }

    int Team::getMaxOfficers() const
    {
        return _team->m_max_officers;
    }

    float Team::getMaxCrew() const
    {
        return _team->m_currentCrewCapacity;
    }

    std::shared_ptr<Race> Team::getRace() const
    {
        return std::make_shared<Race>(_team->m_race);
    }

    void Team::setMaxOfficers(int value)
    {
        _team->m_max_officers = value;
    }

    void Team::setMaxCrew(float value)
    {
        _team->m_currentCrewCapacity = value;
    }

    bool Team::getIsAI() const
    {
        types::AI* ai = *reinterpret_cast<types::AI**>(Address_Ais);
        if(ai)
        {
            types::AI_Team& team = ai->m_team[getNumber()];
            return team.m_enabled && team.m_AI_controlled;
        }
        return false;
    }

    void Team::setIsAI(bool value)
    {
        types::AI* ai = *reinterpret_cast<types::AI**>(Address_Ais);
        if(ai)
        {
            types::AI_Team& team = ai->m_team[getNumber()];
            team.m_AI_controlled = value;
            team.m_enabled       = value;
        }

        types::Transport* transport = LoadMemPointer<types::Transport>(Address_GTransport);

        types::GameSetup& setup =
            (transport->*memory_function<types::GameSetup& (types::Transport::*)()>(Address_GetGameSetup))();

        types::GameSetupSlotDetails details = setup.m_game_setup_details->m_slot_details[getNumber()];

        setup.m_game_setup_details->m_slot_details[getNumber()].m_slot_type = value ? types::ST_COMPUTER_MEDIUM : types::ST_HUMAN ;
    }

    void Team::getEntities(std::vector<EntityPtr>& out) const
    {
        Entities::find(out, entIsTeam, reinterpret_cast<void*>(_team->m_teamNumber));
    }

    ST3D_Colour Team::getColor() const
    {
        return _team->m_teamColor;
    }

    int Team::getNumber() const
    {
        return _team->m_teamNumber;
    }

    float Team::getAmountTraded(eResource resource, eTradeDirection direction, const std::shared_ptr<Team>& other) const
    {
        switch(direction)
        {
        case TradeDir_To:
            {
                switch(resource)
                {
                case RESOURCE_DILITHIUM:
                    return _team->m_dilithiumSent[other->getNumber()];
                    break;
                case RESOURCE_METAL:
                    return _team->m_metalSent[other->getNumber()];
                    break;
                case RESOURCE_CREW:
                    return _team->m_crewSent[other->getNumber()];
                    break;
                case RESOURCE_LATINUM:
                    return _team->m_latinumSent[other->getNumber()];
                    break;
                }
                break;
            }
        case TradeDir_From:
            {
                switch(resource)
                {
                case RESOURCE_DILITHIUM:
                    return _team->m_dilithiumReceieved[other->getNumber()];
                    break;
                case RESOURCE_METAL:
                    return _team->m_metalRecieved[other->getNumber()];
                    break;
                case RESOURCE_CREW:
                    return _team->m_crewReceived[other->getNumber()];
                    break;
                case RESOURCE_LATINUM:
                    return _team->m_latinumRecieved[other->getNumber()];
                    break;
                }
                break;
            }
        }
        return 0;
    }

    eSlotType Team::getSlotType() const
    {
        return static_cast<eSlotType>(_team->m_team_type);
    }

    bool Team::isValid() const
    {
        return nullptr != _team;
    }

    void Team::loadAIP(const std::string& aip) 
    {
        getScriptInterface()->AI_Team_Load_AIP(getNumber(), const_cast<char*>(aip.c_str()));
    }

    void Team::setColor(const ST3D_Colour& color)
    {
        _team->m_teamColor = color;
        _team->m_mapColor = color;
    }

    std::string Team::getName() const
    {
        return _team->m_name_string;
    }

    void Team::setName(const std::string& name)
    {
        _team->m_name_string = name;
    }

    std::shared_ptr<Team::Resources> Team::getResources() const
    {
        return _resources;
    }
}