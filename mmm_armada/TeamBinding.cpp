#include "Team_Internal.h"
#include "Race_Internal.h"
#include "Lua.h"

namespace mmm
{
    namespace
    {
        int metatable = 0;
        std::unordered_map<Team**, std::shared_ptr<Team>> teams;

        template <typename T>
        T* get_self(lua_State* L)
        {
            luaL_checktype(L, 1, LUA_TUSERDATA);
            return *static_cast<T**>(lua_touserdata(L, 1));
        }

        int team_new(lua_State* L)
        {
            luaL_checktype(L, 1, LUA_TNUMBER);
            return team_create(L, std::make_shared<Team>(lua_tointeger(L, 1)));
        }

        int team_index(lua_State* L)
        {
            auto self = get_self<Team>(L);
            const std::string key = lua_tostring(L, 2);

            if (key == "color")
            {
                // TODO
            }
            else if (key == "isAI")
            {
                lua_pushboolean(L, self->getIsAI());
                return 1;
            }
            else if (key == "maxCrew")
            {
                lua_pushnumber(L, self->getMaxCrew());
                return 1;
            }
            else if (key == "maxOfficers")
            {
                lua_pushnumber(L, self->getMaxOfficers());
                return 1;
            }
            else if (key == "name")
            {
                lua_pushstring(L, self->getName().c_str());
                return 1;
            }
            else if (key == "number")
            {
                lua_pushinteger(L, self->getNumber());
                return 1;
            }
            else if (key == "race")
            {
                // TODO
            }
            else if (key == "resources")
            {
                // TODO
            }
            else if (key == "slotType")
            {
                lua_pushinteger(L, self->getSlotType());
                return 1;
            }

            return 0;
        }

        int team_newindex(lua_State* L)
        {
            auto self = get_self<Team>(L);
            const std::string key = lua_tostring(L, 2);

            if (key == "color")
            {
                self->setColor(to_colour(L, 3));
            }
            else if (key == "isAI")
            {
                luaL_checktype(L, 3, LUA_TBOOLEAN);
                self->setIsAI(lua_toboolean(L, 3));
            }
            else if (key == "maxCrew")
            {
                luaL_checktype(L, 3, LUA_TNUMBER);
                self->setMaxCrew(lua_tonumber(L, 3));
            }
            else if (key == "maxOfficers")
            {
                luaL_checktype(L, 3, LUA_TNUMBER);
                self->setMaxOfficers(lua_tonumber(L, 3));
            }
            else if (key == "name")
            {
                luaL_checktype(L, 3, LUA_TSTRING);
                self->setName(lua_tostring(L, 3));
            }

            return 0;
        }

        int team_gc(lua_State* L)
        {
            luaL_checktype(L, 1, LUA_TUSERDATA);
            Team** userdata = static_cast<Team**>(lua_touserdata(L, 1));
            teams.erase(userdata);
            return 0;
        }
    }

    void team_register(lua_State* L)
    {
        lua_pushcfunction(L, team_new);
        lua_setglobal(L, "Player");

        // luaL_newmetatable(L, "team.mt");
        // lua_pushvalue(L, -1);
        lua_newtable(L);

        lua_pushvalue(L, -1);
        metatable = luaL_ref(L, LUA_REGISTRYINDEX);

        lua::add_function(L, -1, team_index, "__index");
        lua::add_function(L, -1, team_newindex, "__newindex");
        lua::add_function(L, -1, team_gc, "__gc");

        /*
        using namespace luabind;

        module(state)
        [
            class_<Team, TeamPtr>( "Player" )
                .def( constructor<int>() )
                .property( "color", &Team::getColor, &Team::setColor )
                .property( "isAI", &Team::getIsAI, &Team::setIsAI )
                .property( "maxCrew", &Team::getMaxCrew, &Team::setMaxCrew )
                .property( "maxOfficers", &Team::getMaxOfficers, &Team::setMaxOfficers )
                .property( "name", &Team::getName, &Team::setName )
                .property( "number", &Team::getNumber )
                .property( "race", &Team::getRace )
                .scope
                [
                    class_<Team::Resources, Team::ResourcesPtr>( "Resources" )
                        .property("dilithium", &Team::Resources::getDilithium, &Team::Resources::setDilithium )
                        .property("metal", &Team::Resources::getMetal, &Team::Resources::setMetal )
                        .property("latinum", &Team::Resources::getLatinum, &Team::Resources::setLatinum )
                        .property("biomatter", &Team::Resources::getBiomatter, &Team::Resources::setBiomatter )
                        .property("crew", &Team::Resources::getCrew, &Team::Resources::setCrew )
                        .property("tritanium", &Team::Resources::getLatinum, &Team::Resources::setLatinum )
                        .property("collectiveConnections", &Team::Resources::getMetal, &Team::Resources::setMetal )
                        .property("supply", &Team::Resources::getBiomatter, &Team::Resources::setBiomatter ),
                    class_<eSlotType>("SlotType")
                        .enum_("constants")
                        [
                            value("None", ST_None),
                            value("Human", ST_Human),
                            value("Observer", ST_Observer),
                            value("AI_Easy", ST_AI_Easy),
                            value("AI_Normal", ST_AI_Normal),
                            value("AI_Hard", ST_AI_Hard ),
                            value("AI_Neural", ST_AI_Neural)
                        ],
                    class_<eTeamRelation>("Relation")
                        .enum_("constants")
                        [
                            value("Enemy", TEAM_ENEMY),
                            value("Neutral", TEAM_NEUTRAL),
                            value("Ally", TEAM_ALLY)
                        ],
                    class_<eTradeDirection>("TradeDirection")
                        .enum_("constants")
                        [
                            value("To", TradeDir_To),
                            value("From", TradeDir_From)
                        ]
                ]
                .property( "resources", &Team::getResources )
                .property( "slotType", &Team::getSlotType )
                .def( "getAmountTraded", &Team::getAmountTraded )
                .def( "getRelation", &Team::getRelation )
                .def( "loadAIP", &Team::loadAIP )
                .def( "setRelation", &Team::setRelation )
        ];*/
    }

    int team_create(lua_State* L, const std::shared_ptr<Team>& team)
    {
        Team** userdata = static_cast<Team**>(lua_newuserdata(L, sizeof(team.get())));
        *userdata = team.get();
        teams[userdata] = team;
        lua_rawgeti(L, LUA_REGISTRYINDEX, metatable);
        lua_setmetatable(L, -2);
        return 1;
    }
}
