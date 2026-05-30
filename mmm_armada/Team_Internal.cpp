#include "Team_Internal.h"
#include "Type_Team.h"
// #include "Type_Entity.h"
// #include "Type_GameObject.h"
#include "Type_AI.h"
#include "Type_DebriefingData.h"

#include "Race_Internal.h"
#include "Entity_Internal.h"
#include "GameObject_Internal.h"
#include "Entities_Internal.h"
#include "LuaBinding.h"


namespace mmm
{
    namespace
    {
        constexpr std::size_t Address_SetRelation = 0x004971d0;
        constexpr std::size_t Address_GetTeam = 0x00496340;
        constexpr std::size_t Address_GTransport = 0x0076b8d4;
        constexpr std::size_t Address_GetGameSetup = 0x00557930;

        constexpr std::size_t Address_s_missionRace = 0x00737cc0;
        constexpr std::size_t Address_gCameraManager = 0x00763370;
        constexpr std::size_t Address_DisplayInterface_Cleanup = 0x0051a8c0;
        constexpr std::size_t Address_DisplayInterface_InitAll = 0x0051a640;
        constexpr std::size_t Address_DisplayInterface_PostLoadAll = 0x0051a6e0;

        int team_metatable{ LUA_NOREF };

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

        void DisplayInterface_InitAll()
        {
            memory_function<void(__cdecl*)()>(Address_DisplayInterface_InitAll)();
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

        bool entIsTeam(const std::shared_ptr<Entity>& ent, void* arguments)
        {
            return ent &&
                ent->isType(Entity_GameObject) &&
                std::static_pointer_cast<GameObject>(ent)->getTeam()->getNumber() == reinterpret_cast<int>(arguments);
        }

        int resources_index(lua_State* L)
        {
            const auto self = get_userdata<std::shared_ptr<Team::Resources>>(L, 1);
            const std::string key = lua_tostring(L, 2);

            if (key == "dilithium")
            {
                lua_pushnumber(L, self->getDilithium());
                return 1;
            }
            else if (key == "metal" || key == "collectiveConnections")
            {
                lua_pushnumber(L, self->getMetal());
                return 1;
            }
            else if (key == "latinum" || key == "tritanium")
            {
                lua_pushnumber(L, self->getLatinum());
                return 1;
            }
            else if (key == "biomatter" || key == "supply")
            {
                lua_pushnumber(L, self->getBiomatter());
                return 1;
            }
            else if (key == "crew")
            {
                lua_pushnumber(L, self->getCrew());
                return 1;
            }

            return 0;
        }

        int resources_newindex(lua_State* L)
        {
            auto self = get_userdata<std::shared_ptr<Team::Resources>>(L, 1);
            const std::string key = lua_tostring(L, 2);
            const float value = lua_tonumber(L, 3);

            if (key == "dilithium")
            {
                self->setDilithium(value);
                return 0;
            }
            else if (key == "metal" || key == "collectiveConnections")
            {
                self->setMetal(value);
                return 0;
            }
            else if (key == "latinum" || key == "tritanium")
            {
                self->setLatinum(value);
                return 0;
            }
            else if (key == "biomatter" || key == "supply")
            {
                self->setBiomatter(value);
                return 0;
            }
            else if (key == "crew")
            {
                self->setCrew(value);
                return 0;
            }

            return 0;
        }

        int resources_new(lua_State* L, const std::shared_ptr<Team::Resources>& resources)
        {
            create_userdata(L, resources);
            create_metatable(L,
                {
                    { "__index", resources_index },
                    { "__newindex", resources_newindex }
                });
            return 1;
        }

        int team_gc(lua_State* L)
        {
            cleanup_userdata<std::shared_ptr<Team>>(L);
            return 0;
        }

        int team_get_amount_traded(lua_State* L)
        {
            const auto team = get_userdata<std::shared_ptr<Team>>(L, 1);
            const auto resource = static_cast<eResource>(lua_tonumber(L, 2));
            const auto direction = static_cast<eTradeDirection>(lua_tonumber(L, 3));
            const auto other = get_userdata<std::shared_ptr<Team>>(L, 4);
            lua_pushnumber(L, team->getAmountTraded(resource, direction, other));
            return 1;
        }

        int team_get_relation(lua_State* L)
        {
            const auto team = get_userdata<std::shared_ptr<Team>>(L, 1);
            const auto other = get_userdata<std::shared_ptr<Team>>(L, 2);
            lua_pushnumber(L, team->getRelation(other));
            return 1;
        }

        int team_get_slot_type(lua_State* L)
        {
            const auto team = get_userdata<std::shared_ptr<Team>>(L, 1);
            lua_pushnumber(L, team->getSlotType());
            return 1;
        }

        int team_load_aip(lua_State* L)
        {
            const auto team = get_userdata<std::shared_ptr<Team>>(L, 1);
            const auto aip = lua_tostring(L, 2);
            team->loadAIP(aip);
            return 0;
        }

        int team_set_relation(lua_State* L)
        {
            const auto team = get_userdata<std::shared_ptr<Team>>(L, 1);
            const auto other_team = get_userdata<std::shared_ptr<Team>>(L, 2);
            const eTeamRelation relation = static_cast<eTeamRelation>(lua_tonumber(L, 3));
            team->setRelation(other_team, relation);
            return 0;
        }

        int team_index(lua_State* L)
        {
            const auto team = get_userdata<std::shared_ptr<Team>>(L, 1);
            const std::string key = lua_tostring(L, 2);

            if (key == "color")
            {
                return colour_new(L, team->getColor());
            }
            else if (key == "getAmountTraded")
            {
                lua_pushcfunction(L, team_get_amount_traded);
                return 1;
            }
            else if (key == "getRelation")
            {
                lua_pushcfunction(L, team_get_relation);
                return 1;
            }
            else if (key == "isAI")
            {
                lua_pushboolean(L, team->getIsAI());
                return 1;
            }
            else if (key == "loadAIP")
            {
                lua_pushcfunction(L, team_load_aip);
                return 1;
            }
            else if (key == "maxCrew")
            {
                lua_pushnumber(L, team->getMaxCrew());
                return 1;
            }
            else if (key == "maxOfficers")
            {
                lua_pushnumber(L, team->getMaxOfficers());
                return 1;
            }
            else if (key == "name")
            {
                lua_pushstring(L, team->getName().c_str());
                return 1;
            }
            else if (key == "number")
            {
                lua_pushnumber(L, team->getNumber());
                return 1;
            }
            else if (key == "race")
            {
                return race_new(L, team->getRace());
            }
            else if (key == "resources")
            {
                return resources_new(L, team->getResources());
            }
            else if (key == "setRelation")
            {
                lua_pushcfunction(L, team_set_relation);
                return 1;
            }
            else if (key == "slotType")
            {
                lua_pushcfunction(L, team_get_slot_type);
                return 1;
            }
            else if (key == "useWormholes")
            {
                lua_pushboolean(L, team->getUseWormholes());
                return 1;
            }

            return 0;
        }

        int team_newindex(lua_State* L)
        {
            const auto team = get_userdata<std::shared_ptr<Team>>(L, 1);
            const std::string key = lua_tostring(L, 2);

            if (key == "color")
            {
                team->setColor(get_userdata<ST3D_Colour>(L, 3));
                return 0;
            }
            else if (key == "isAI")
            {
                team->setIsAI(lua_toboolean(L, 3));
                return 0;
            }
            else if (key == "maxCrew")
            {
                team->setMaxCrew(lua_tonumber(L, 3));
                return 0;
            }
            else if (key == "maxOfficers")
            {
                team->setMaxOfficers(lua_tonumber(L, 3));
                return 0;
            }
            else if (key == "name")
            {
                team->setName(lua_tostring(L, 3));
                return 0;
            }
            else if (key == "race")
            {
                team->setRace(get_userdata<std::shared_ptr<Race>>(L, 3));
                return 0;
            }
            else if (key == "useWormholes")
            {
                team->setUseWormholes(lua_toboolean(L, 3));
                return 0;
            }
            return 0;
        }

        int team_call(lua_State* L)
        {
            return team_new(L, std::make_shared<Team>(lua_tonumber(L, 2)));
        }
    }

    Team::Team(int number)
        : team_(0)
    {
        typedef types::Team& (*MemFunction)( int );
        MemFunction function = memory_function< MemFunction >( Address_GetTeam );
        team_ = &function( number );
        resources_ = std::make_shared<Resources>(team_);
    }

    Team::Team(types::Team* team)
        : team_(team), resources_(std::make_shared<Resources>(team_))
    {

    }

    eTeamRelation Team::getRelation(const std::shared_ptr<Team>& other) const
    {
        return team_->m_relationship[other->getNumber()];
    }

    void Team::setRelation(const std::shared_ptr<Team>& other, eTeamRelation relation)
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

    std::shared_ptr<Race> Team::getRace() const
    {
        return std::make_shared<Race>(team_->m_race);
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
            team.m_enabled = value;
        }

        types::Transport* transport = LoadMemPointer<types::Transport>(Address_GTransport);

        types::GameSetup& setup = (transport->*memory_function<types::GameSetup& (types::Transport::*)()>(Address_GetGameSetup))();

        types::GameSetupSlotDetails details = setup.m_game_setup_details->m_slot_details[getNumber()];

        setup.m_game_setup_details->m_slot_details[getNumber()].m_slot_type = value ? types::ST_COMPUTER_MEDIUM : types::ST_HUMAN;
    }

    void Team::getEntities(std::vector<std::shared_ptr<Entity>>& out) const
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

    float Team::getAmountTraded(eResource resource, eTradeDirection direction, const std::shared_ptr<Team>& other) const
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
                switch(resource)
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
        types::get_debriefing_data()->m_team_data[team_->m_teamNumber]->m_name = name;
    }

    Team::ResourcesPtr Team::getResources() const
    {
        return resources_;
    }

    void Team::setRace(const std::shared_ptr<Race>& race)
    {
        if (!race->getRace())
        {
            return;
        }

        team_->m_race = race->getRace();

        auto debriefing = types::get_debriefing_data();
        debriefing->m_team_data[team_->m_teamNumber]->m_race = race->getName();
        debriefing->m_team_data[team_->m_teamNumber]->m_actualRace = race->getName();

        if (!team_->m_is_ai)
        {
            SetMissionRace(race->getRace());
            const auto interest = GetCameraInterest();
            DisplayInterface_Cleanup();
            DisplayInterface_InitAll();
            DisplayInterface_PostLoadAll();
            SetCameraInterest(interest);
        }
    }

    bool Team::getUseWormholes() const
    {
        types::AI* ai = *reinterpret_cast<types::AI**>(0x00735bc4);
        return ai->m_team[team_->m_teamNumber].m_useWormholes;
    }

    void Team::setUseWormholes(bool enabled)
    {
        types::AI* ai = *reinterpret_cast<types::AI**>(0x00735bc4);
        ai->m_team[team_->m_teamNumber].m_useWormholes = enabled;
    }

    int team_new(lua_State* L, const std::shared_ptr<Team>& team)
    {
        create_userdata(L, team);
        assign_metatable(L, team_metatable);
        return 1;
    }

    void team_register(lua_State* L)
    {
        lua_newtable(L);
        create_metatable(L,
            {
                { "__call", team_call }
            });
        create_enum(L, "Relation",
            {
                { "Enemy", TEAM_ENEMY },
                { "Neutral", TEAM_NEUTRAL },
                { "Ally", TEAM_ALLY }
            });
        create_enum(L, "SlotType",
            {
                { "None", ST_None },
                { "Human", ST_Human },
                { "Observer", ST_Observer },
                { "AI_Easy", ST_AI_Easy },
                { "AI_Normal", ST_AI_Normal },
                { "AI_Hard", ST_AI_Hard },
                { "AI_Neural", ST_AI_Neural }
            });
        create_enum(L, "TradeDirection",
            {
                { "To", TradeDir_To },
                { "From", TradeDir_From }
            });
        lua_setglobal(L, "Player");

        team_metatable = store_metatable(L,
            {
                { "__index", team_index },
                { "__newindex", team_newindex },
                { "__gc", team_gc }
            });
    }
}