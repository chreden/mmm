#include "UI_Internal.h"
#include "Lua.h"

namespace mmm
{
    namespace 
    {
        UI ui;

        int add_message(lua_State* L)
        {
            if (lua_gettop(L) != 8)
            {
                return luaL_error(L, "UI:addMessage expects 8 arguments, got %d.\n\
UI:addMessage(string message, number x, number y, Justify justify, Color color, boolean fade, float displayTime)", lua_gettop(L));
            }

            luaL_checktype(L, 2, LUA_TSTRING);
            luaL_checktype(L, 3, LUA_TNUMBER);
            luaL_checktype(L, 4, LUA_TNUMBER);
            luaL_checktype(L, 5, LUA_TNUMBER);
            luaL_checktype(L, 6, LUA_TUSERDATA);
            luaL_checktype(L, 7, LUA_TBOOLEAN);
            luaL_checktype(L, 8, LUA_TNUMBER);

            ui.addMessage(lua_tostring(L, 2), lua_tointeger(L, 3), lua_tointeger(L, 4), static_cast<mmm::eJustify>(lua_tointeger(L, 5)),
                to_colour(L, 6), lua_toboolean(L, 7), lua_tonumber(L, 8));

            return 0;
        }

        int add_minimap_mark(lua_State* L)
        {
            if (lua_gettop(L) != 5)
            {
                return luaL_error(L, "UI:addTitle expects 5 arguments, got %d.\n\
UI:addMinimapMark(Vector message, number radius, number shrinkRate, Color color)", lua_gettop(L));
            }

            luaL_checktype(L, 2, LUA_TUSERDATA);
            luaL_checktype(L, 3, LUA_TNUMBER);
            luaL_checktype(L, 4, LUA_TNUMBER);
            luaL_checktype(L, 5, LUA_TUSERDATA);

            ui.addMinimapMark(to_vector(L, 2), lua_tointeger(L, 3), lua_tonumber(L, 4), to_colour(L, 5));
            return 0;
        }

        int show_trades_to(lua_State* L)
        {
            if (lua_gettop(L) != 2)
            {
                return luaL_error(L, "UI:showTradesTo expects 2 arguments, got %d.\n\
UI:showTradesTo(Team team)", lua_gettop(L));
            }

            luaL_checktype(L, 2, LUA_TUSERDATA);

            // Luabind TODO: Use non-luabind version of team - will not function until then:
            TeamPtr team;
            ui.showTradesTo(team);
            return 0;
        }

        int add_title(lua_State* L)
        {
            if (lua_gettop(L) != 6)
            {
                return luaL_error(L, "UI:addTitle expects 6 arguments, got %d.\n\
UI:addTitle(string message, number x, number y, number time, boolean fade)", lua_gettop(L));
            }

            luaL_checktype(L, 2, LUA_TSTRING);
            luaL_checktype(L, 3, LUA_TNUMBER);
            luaL_checktype(L, 4, LUA_TNUMBER);
            luaL_checktype(L, 5, LUA_TNUMBER);
            luaL_checktype(L, 6, LUA_TBOOLEAN);

            ui.addTitle(lua_tostring(L, 2), lua_tointeger(L, 3), lua_tointeger(L, 4), lua_tonumber(L, 5), lua_toboolean(L, 6));
            return 0;
        }

        int add_subtitle(lua_State* L)
        {
            if (lua_gettop(L) != 6)
            {
                return luaL_error(L, "UI:addSubtitle expects 6 arguments, got %d.\n\
UI:addSubtitle(string message, number x, number y, number time, boolean fade)", lua_gettop(L));
            }

            luaL_checktype(L, 2, LUA_TSTRING);
            luaL_checktype(L, 3, LUA_TNUMBER);
            luaL_checktype(L, 4, LUA_TNUMBER);
            luaL_checktype(L, 5, LUA_TNUMBER);
            luaL_checktype(L, 6, LUA_TBOOLEAN);

            ui.addSubtitle(lua_tostring(L, 2), lua_tointeger(L, 3), lua_tointeger(L, 4), lua_tonumber(L, 5), lua_toboolean(L, 6));
        }

        int ui_index(lua_State* L)
        {
            const std::string key = lua_tostring(L, 2);

            if (key == "teamText")
            {
                lua_pushstring(L, ui.getTeamText().c_str());
                return 1;
            }
            else if (key == "addMessage")
            {
                lua_pushcfunction(L, add_message);
                return 1;
            }
            else if (key == "addMinimapMark")
            {
                lua_pushcfunction(L, add_minimap_mark);
                return 1;
            }
            else if (key == "showTradesTo")
            {
                lua_pushcfunction(L, show_trades_to);
                return 1;
            }
            else if (key == "addTitle")
            {
                lua_pushcfunction(L, add_title);
                return 1;
            }
            else if (key == "addSubtitle")
            {
                lua_pushcfunction(L, add_subtitle);
                return 1;
            }

            return 0;
        }

        int ui_newindex(lua_State* L)
        {
            const std::string key = lua_tostring(L, 2);

            if (key == "teamText")
            {
                luaL_checktype(L, -1, LUA_TSTRING);
                ui.setTeamText(lua_tostring(L, -1));
            }

            return 0;
        }

        int ui_gc(lua_State* L)
        {
            return 0;
        }
    }

    void ui_register(lua_State* L)
    {
        lua_newtable(L);
        lua::set_enum(L, "Justify", -1,
            {
                { "TopLeft", JUSTIFY_TOP_LEFT },
                { "TopRight", JUSTIFY_TOP_RIGHT },
                { "TopCenter", JUSTIFY_TOP_CENTER },
                { "BottomLeft", JUSTIFY_BOTTOM_LEFT },
                { "BottomRight", JUSTIFY_BOTTOM_RIGHT },
                { "BottomCenter", JUSTIFY_BOTTOM_CENTER },
                { "CenterLeft", JUSTIFY_CENTER_LEFT },
                { "CenterRight", JUSTIFY_CENTER_RIGHT },
                { "Center", JUSTIFY_CENTER },
                { "TopLeftByLine", JUSTIFY_TOP_LEFT_BY_LINE },
                { "TopRightByLine", JUSTIFY_TOP_RIGHT_BY_LINE },
                { "TopCenterByLine", JUSTIFY_TOP_CENTER_BY_LINE },
                { "BottomLeftByLine", JUSTIFY_BOTTOM_LEFT_BY_LINE },
                { "BottomRightByLine", JUSTIFY_BOTTOM_RIGHT_BY_LINE },
                { "BottomCenterByLine", JUSTIFY_BOTTOM_CENTER_BY_LINE },
                { "CenterLeftByLine", JUSTIFY_CENTER_LEFT_BY_LINE },
                { "CenterRightByLine", JUSTIFY_CENTER_RIGHT_BY_LINE },
                { "CenterByLine", JUSTIFY_CENTER_BY_LINE }
            });

        lua_newtable(L);
        lua_pushcfunction(L, ui_index);
        lua_setfield(L, -2, "__index");
        lua_pushcfunction(L, ui_newindex);
        lua_setfield(L, -2, "__newindex");
        lua_setmetatable(L, -2);

        lua_setglobal(L, "UI");
    }
}