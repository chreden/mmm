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
        constexpr std::size_t Address_SetRelation	= 0x004971d0;
        constexpr std::size_t Address_GetTeam		= 0x00496340;
        constexpr std::size_t Address_GTransport	= 0x0076b8d4;
        constexpr std::size_t Address_GetGameSetup	= 0x00557930;

        constexpr std::size_t Address_s_missionRace = 0x00737cc0;
        constexpr std::size_t Address_gCameraManager = 0x00763370;
        constexpr std::size_t Address_DisplayInterface_Cleanup = 0x0051a8c0;
        constexpr std::size_t Address_DisplayInterface_PostLoadAll = 0x0051a6e0;

        struct GameCamera
        {
            std::size_t* vtable;
        };

        struct CameraManager
        {
            GameCamera* m_pCamera;
        };

        void SetMissionRace(types::Race* race)
        {
            *reinterpret_cast<types::Race**>(Address_s_missionRace) = race;
        }

        Vector3 GetCameraInterest()
        {
            CameraManager* camera_manager = reinterpret_cast<CameraManager*>(Address_gCameraManager);
            return *(camera_manager->m_pCamera->*memory_function<Vector3 * (GameCamera::*)()>
                (camera_manager->m_pCamera->vtable[23]))();
        }

        void DisplayInterface_Cleanup()
        {
            memory_function<void(__cdecl*)()>(Address_DisplayInterface_Cleanup)();
        }

        void DisplayInterface_PostLoadAll()
        {
            memory_function<void(__cdecl*)()>(Address_DisplayInterface_PostLoadAll)();
        }

        void SetCameraInterest(const Vector3& interest)
        {
            CameraManager* camera_manager = reinterpret_cast<CameraManager*>(Address_gCameraManager);
            (camera_manager->m_pCamera->*memory_function<void (GameCamera::*)(const Vector3*)>
                (camera_manager->m_pCamera->vtable[21]))(&interest);
        }

        bool entIsTeam(EntityPtr ent, void* arguments)
        {
            return ent &&
                ent->isType(Entity_GameObject) &&
                boost::static_pointer_cast<GameObject>(ent)->getTeam()->getNumber() == reinterpret_cast<int>(arguments);
        }
    }

    Team::Team(int number)
        : team_(0)
    {
        typedef types::Team& (*MemFunction)( int );
        MemFunction function = memory_function< MemFunction >( Address_GetTeam );
        team_ = &function( number );
        resources_ = ResourcesPtr(new Resources(team_));
    }

    Team::Team(types::Team* team)
        : team_(team), resources_(new Resources(team_))
    {

    }

    eTeamRelation Team::getRelation(TeamPtr other) const
    {
        return team_->m_relationship[other->getNumber()];
    }

    void Team::setRelation(TeamPtr other, eTeamRelation relation)
    {
        //Ok, so setting manually and setting relations with script interface didn't actually
        //work, so I guess this is the only way to do it. It works fine though.
        team_->m_relationship[other->getNumber()] = relation;
        other->team_->m_relationship[getNumber()] = relation;
    }

    int Team::getMaxOfficers() const
    {
        return team_->m_max_officers;
    }

    float Team::getMaxCrew() const
    {
        return team_->m_currentCrewCapacity;
    }

    RacePtr Team::getRace() const
    {
        return RacePtr(new Race(team_->m_race));
    }

    void Team::setMaxOfficers(int value)
    {
        team_->m_max_officers = value;
    }

    void Team::setMaxCrew(float value)
    {
        team_->m_currentCrewCapacity = value;
    }

    bool Team::getIsAI() const
    {
        types::AI* ai = *reinterpret_cast<types::AI**>(0x00735bc4);
        if( ai )
        {
            types::AI_Team& team = ai->m_team[getNumber()];
            return team.m_enabled && team.m_AI_controlled;
        }
        return false;
    }

    void Team::setIsAI(bool value)
    {
        types::AI* ai = *reinterpret_cast<types::AI**>(0x00735bc4);
        if( ai )
        {
            types::AI_Team& team = ai->m_team[getNumber()];
            team.m_AI_controlled = value;
            team.m_enabled		 = value;
        }

        types::Transport* transport = LoadMemPointer<types::Transport>(Address_GTransport);

        types::GameSetup& setup = (transport->*memory_function<types::GameSetup& (types::Transport::*)()>(Address_GetGameSetup))();

        types::GameSetupSlotDetails details = setup.m_game_setup_details->m_slot_details[getNumber()];

        setup.m_game_setup_details->m_slot_details[getNumber()].m_slot_type = value ? types::ST_COMPUTER_MEDIUM : types::ST_HUMAN;
    }

    void Team::getEntities(std::vector<EntityPtr>& out) const
    {
        Entities::find(out, entIsTeam, reinterpret_cast<void*>(team_->m_teamNumber));
    }

    ST3D_Colour Team::getColor() const
    {
        return team_->m_teamColor;
    }

    int Team::getNumber() const
    {
        return team_->m_teamNumber;
    }

    float Team::getAmountTraded(eResource resource, eTradeDirection direction, TeamPtr other) const
    {
        switch(direction)
        {
        case TradeDir_To:
            {
                switch(resource)
                {
                case RESOURCE_DILITHIUM:
                    return team_->m_dilithiumSent[other->getNumber()];
                    break;
                case RESOURCE_METAL:
                    return team_->m_metalSent[other->getNumber()];
                    break;
                case RESOURCE_CREW:
                    return team_->m_crewSent[other->getNumber()];
                    break;
                case RESOURCE_LATINUM:
                    return team_->m_latinumSent[other->getNumber()];
                    break;
                }
                break;
            }
        case TradeDir_From:
            {
                switch( resource )
                {
                case RESOURCE_DILITHIUM:
                    return team_->m_dilithiumReceieved[other->getNumber()];
                    break;
                case RESOURCE_METAL:
                    return team_->m_metalRecieved[other->getNumber()];
                    break;
                case RESOURCE_CREW:
                    return team_->m_crewReceived[other->getNumber()];
                    break;
                case RESOURCE_LATINUM:
                    return team_->m_latinumRecieved[other->getNumber()];
                    break;
                }
                break;
            }
        }
        return 0;
    }

    eSlotType Team::getSlotType() const
    {
        return static_cast<eSlotType>(team_->m_team_type);
    }

    bool Team::isValid() const
    {
        return nullptr != team_;
    }

    void Team::loadAIP(const std::string& aip) 
    {
        getScriptInterface()->AI_Team_Load_AIP(getNumber(), const_cast<char*>(aip.c_str()));
    }

    void Team::setColor(const ST3D_Colour& color)
    {
        team_->m_teamColor = color;
        team_->m_mapColor = color;
    }

    const std::string Team::getName() const
    {
        return team_->m_name_string;
    }

    void Team::setName(const std::string& name)
    {
        team_->m_name_string = name;
    }

    Team::ResourcesPtr Team::getResources() const
    {
        return resources_;
    }

    void Team::setRace(RacePtr race)
    {
        if (!race->getRace())
        {
            return;
        }

        team_->m_race = race->getRace();
        if (!team_->m_is_ai)
        {
            SetMissionRace(race->getRace());
            const auto interest = GetCameraInterest();
            DisplayInterface_Cleanup();
            DisplayInterface_PostLoadAll();
            SetCameraInterest(interest);
        }
    }
}