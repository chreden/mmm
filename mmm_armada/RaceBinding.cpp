#include "Race_Internal.h"
#include "Lua.h"

namespace mmm
{
    namespace
    {
        int metatable;
        std::unordered_map<Race**, std::shared_ptr<Race>> races;

        int race_index(lua_State* L)
        {
            auto self = lua::get_self<Race>(L);
            std::string key = lua_tostring(L, 2);

            if (key == "boardingStrength")
            {
                lua_pushnumber(L, self->getBoardingStrength());
                return 1;
            }
            else if (key == "displayName")
            {
                lua_pushstring(L, self->getDisplayName().c_str());
                return 1;
            }
            else if (key == "name")
            {
                lua_pushstring(L, self->getName().c_str());
                return 1;
            }
            else if (key == "repairStrength")
            {
                lua_pushnumber(L, self->getRepairStrength());
                return 1;
            }
            else if (key == "number")
            {
                lua_pushinteger(L, self->getNumber());
                return 1;
            }

            return 0;
        }

        int race_newindex(lua_State* L)
        {
            return 0;
        }

        int race_gc(lua_State* L)
        {
            luaL_checktype(L, 1, LUA_TUSERDATA);
            Race** userdata = static_cast<Race**>(lua_touserdata(L, 1));
            races.erase(userdata);
            return 0;
        }

        int race_find(lua_State* L)
        {
            if (lua_type(L, 1) == LUA_TNUMBER)
            {
                auto result = Race::find(lua_tointeger(L, 1));
                return race_create(L, result);
            }
            else if (lua_type(L, 1) == LUA_TSTRING)
            {
                auto results = Race::getAll();
            }

            luaL_error(L, "Race.find expects 1 argument, either string or number.\n\
Race.find(string name)\n\
Race.find(number raceNumber)");

            return 0;
        }

        int race_get_all(lua_State* L)
        {
            lua_newtable(L);
            const auto results = Race::getAll();
            for (int i = 0; i < results.size(); ++i)
            {
                race_create(L, results[i]);
                lua_rawseti(L, -2, i + 1);
            }
            return 1;
        }
    }

    int race_create(lua_State* L, const std::shared_ptr<Race>& race)
    {
        if (race == nullptr)
        {
            lua_pushnil(L);
        }

        Race** userdata = static_cast<Race**>(lua_newuserdata(L, sizeof(race.get())));
        *userdata = race.get();
        races[userdata] = race;
        lua_rawgeti(L, LUA_REGISTRYINDEX, metatable);
        lua_setmetatable(L, -2);
        return 1;
    }

    void race_register( lua_State* L )
    {
        lua_newtable(L);
        lua_pushcfunction(L, race_find);
        lua_setfield(L, -2, "find");
        lua_pushcfunction(L, race_get_all);
        lua_setfield(L, -2, "getAll");
        lua_setglobal(L, "Race");

        lua_newtable(L);
        lua_pushvalue(L, -1);
        metatable = luaL_ref(L, LUA_REGISTRYINDEX);
        lua::add_function(L, -1, race_index, "__index");
        lua::add_function(L, -1, race_newindex, "__newindex");
        lua::add_function(L, -1, race_gc, "__gc");
    }
}
