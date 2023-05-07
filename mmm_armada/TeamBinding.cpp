#include "Team_Internal.h"
#include "Race_Internal.h"
#include "Lua.h"

namespace mmm
{
    namespace
    {
        int metatable = 0;
        int resources_metatable = 0;

        std::unordered_map<Team**, std::shared_ptr<Team>> teams;
        std::unordered_map<Team::Resources**, std::shared_ptr<Team::Resources>> resources;

        int resources_create(lua_State* L, const std::shared_ptr<Team::Resources>& resource)
        {
            Team::Resources** userdata = static_cast<Team::Resources**>(lua_newuserdata(L, sizeof(resource.get())));
            *userdata = resource.get();
            resources[userdata] = resource;
            lua_rawgeti(L, LUA_REGISTRYINDEX, resources_metatable);
            lua_setmetatable(L, -2);
            return 1;
        }

        template <typename T>
        T* get_self(lua_State* L)
        {
            luaL_checktype(L, 1, LUA_TUSERDATA);
            return *static_cast<T**>(lua_touserdata(L, 1));
        }

        int team_get_amount_traded(lua_State* L)
        {
            auto self = get_self<Team>(L);

            luaL_checktype(L, 2, LUA_TNUMBER);
            luaL_checktype(L, 3, LUA_TNUMBER);
            luaL_checktype(L, 4, LUA_TUSERDATA);
            
            lua_pushnumber(L, self->getAmountTraded(
                static_cast<eResource>(lua_tointeger(L, 2)),
                static_cast<eTradeDirection>(lua_tointeger(L, 3)),
                to_team(L, 4)));
            return 1;
        }

        int team_get_relation(lua_State* L)
        {
            auto self = get_self<Team>(L);
            luaL_checktype(L, 2, LUA_TUSERDATA);
            lua_pushinteger(L, self->getRelation(to_team(L, 2)));
            return 1;
        }

        int team_load_aip(lua_State* L)
        {
            auto self = get_self<Team>(L);
            luaL_checktype(L, 2, LUA_TSTRING);
            self->loadAIP(lua_tostring(L, 2));
            return 0;
        }

        int team_set_relation(lua_State* L)
        {
            auto self = get_self<Team>(L);
            luaL_checktype(L, 2, LUA_TUSERDATA);
            luaL_checktype(L, 3, LUA_TNUMBER);
            self->setRelation(to_team(L, 2), static_cast<eTeamRelation>(lua_tointeger(L, 3)));
            return 0;
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
                return create_colour(L, self->getColor());
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
                lua_pushboolean(L, self->getIsAI());
                return 1;
            }
            else if (key == "loadAIP")
            {
                lua_pushcfunction(L, team_load_aip);
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
                return race_create(L, self->getRace());
            }
            else if (key == "resources")
            {
                return resources_create(L, self->getResources());
            }
            else if (key == "setRelation")
            {
                lua_pushcfunction(L, team_set_relation);
                return 1;
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

        int resources_index(lua_State* L)
        {
            auto self = get_self<Team::Resources>(L);
            const std::string key = lua_tostring(L, 2);

            if (key == "dilithium")
            {
                lua_pushnumber(L, self->getDilithium());
                return 1;
            }
            else if (key == "metal")
            {
                lua_pushnumber(L, self->getMetal());
                return 1;
            }
            else if (key == "latinum")
            {
                lua_pushnumber(L, self->getLatinum());
                return 1;
            }
            else if (key == "biomatter")
            {
                lua_pushnumber(L, self->getBiomatter());
                return 1;
            }
            else if (key == "crew")
            {
                lua_pushnumber(L, self->getCrew());
                return 1;
            }
            else if (key == "tritanium")
            {
                lua_pushnumber(L, self->getLatinum());
                return 1;
            }
            else if (key == "collectiveConnections")
            {
                lua_pushnumber(L, self->getMetal());
                return 1;
            }
            else if (key == "supply")
            {
                lua_pushnumber(L, self->getBiomatter());
                return 1;
            }

            return 0;
        }

        int resources_newindex(lua_State* L)
        {
            auto self = get_self<Team::Resources>(L);
            const std::string key = lua_tostring(L, 2);

            if (key == "dilithium")
            {
                luaL_checktype(L, 3, LUA_TNUMBER);
                self->setDilithium(lua_tonumber(L, 3));
            }
            else if (key == "metal")
            {
                luaL_checktype(L, 3, LUA_TNUMBER);
                self->setMetal(lua_tonumber(L, 3));
            }
            else if (key == "latinum")
            {
                luaL_checktype(L, 3, LUA_TNUMBER);
                self->setLatinum(lua_tonumber(L, 3));
            }
            else if (key == "biomatter")
            {
                luaL_checktype(L, 3, LUA_TNUMBER);
                self->setBiomatter(lua_tonumber(L, 3));
            }
            else if (key == "crew")
            {
                luaL_checktype(L, 3, LUA_TNUMBER);
                self->setCrew(lua_tonumber(L, 3));
            }
            else if (key == "tritanium")
            {
                luaL_checktype(L, 3, LUA_TNUMBER);
                self->setLatinum(lua_tonumber(L, 3));
            }
            else if (key == "collectiveConnections")
            {
                luaL_checktype(L, 3, LUA_TNUMBER);
                self->setMetal(lua_tonumber(L, 3));
            }
            else if (key == "supply")
            {
                luaL_checktype(L, 3, LUA_TNUMBER);
                self->setBiomatter(lua_tonumber(L, 3));
            }

            return 0;
        }

        int resources_gc(lua_State* L)
        {
            luaL_checktype(L, 1, LUA_TUSERDATA);
            Team::Resources** userdata = static_cast<Team::Resources**>(lua_touserdata(L, 1));
            resources.erase(userdata);
            return 0;
        }
    }

    void resources_register(lua_State* L)
    {
        lua_newtable(L);
        lua_pushvalue(L, -1);
        resources_metatable = luaL_ref(L, LUA_REGISTRYINDEX);
        lua::add_function(L, -1, resources_index, "__index");
        lua::add_function(L, -1, resources_newindex, "__newindex");
        lua::add_function(L, -1, resources_gc, "__gc");
    }

    void team_register(lua_State* L)
    {
        lua_pushcfunction(L, team_new);
        lua_setglobal(L, "Player");

        lua_newtable(L);
        lua_pushvalue(L, -1);
        metatable = luaL_ref(L, LUA_REGISTRYINDEX);
        lua::add_function(L, -1, team_index, "__index");
        lua::add_function(L, -1, team_newindex, "__newindex");
        lua::add_function(L, -1, team_gc, "__gc");

        lua::set_enum(L, "SlotType", -1,
            {
                { "None", ST_None },
                { "Human", ST_Human },
                { "Observer", ST_Observer },
                { "AI_Easy", ST_AI_Easy },
                { "AI_Normal", ST_AI_Normal },
                { "AI_Hard", ST_AI_Hard },
                { "AI_Neural", ST_AI_Neural },
            });

        lua::set_enum(L, "Relation", -1,
            {
                { "Enemy", TEAM_ENEMY },
                { "Neutral", TEAM_NEUTRAL },
                { "Ally", TEAM_ALLY },
            });

        lua::set_enum(L, "TradeDirection", -1,
            {
                { "To", TradeDir_To },
                { "From", TradeDir_From }
            });

        resources_register(L);
    }

    int team_create(lua_State* L, const std::shared_ptr<Team>& team)
    {
        if (team == nullptr)
        {
            lua_pushnil(L);
            return 1;
        }

        Team** userdata = static_cast<Team**>(lua_newuserdata(L, sizeof(team.get())));
        *userdata = team.get();
        teams[userdata] = team;
        lua_rawgeti(L, LUA_REGISTRYINDEX, metatable);
        lua_setmetatable(L, -2);
        return 1;
    }

    std::shared_ptr<Team> to_team(lua_State* L, int index)
    {
        luaL_checktype(L, index, LUA_TUSERDATA);
        Team** userdata = static_cast<Team**>(lua_touserdata(L, index));
        auto found = teams.find(userdata);
        if (found != teams.end())
        {
            return found->second;
        }
        return nullptr;
    }
}
