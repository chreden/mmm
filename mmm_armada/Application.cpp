#include "Application.h"
#include "ScriptErrors.h"
#include <format>

namespace mmm
{
    namespace
    {
        struct MMMApp
        {

        };
        int  app_ref{ -2 };
        bool cineractive{ false };
        lua_State* lua_state{ nullptr };

        void application_cineractiveUpdate()
        {
            if (app_ref != -2)
            {
                lua_rawgeti(lua_state, LUA_REGISTRYINDEX, app_ref);
                lua_getfield(lua_state, -1, "cineractiveUpdate");
                if (lua_isnil(lua_state, -1))
                {
                    lua_pop(lua_state, 2);
                    return;
                }
                lua_rawgeti(lua_state, LUA_REGISTRYINDEX, app_ref);
                if (LUA_OK != lua_pcall(lua_state, 1, 0, 0))
                {
                    scriptError(std::format("Error in cineractiveUpdate: {}", lua_tostring(lua_state, -1)));
                }
            }
        }

        int application_app_register(lua_State* L)
        {
            app_ref = luaL_ref(L, LUA_REGISTRYINDEX);
            return 0;
        }
    }

    bool application_isCineractive()
    {
        return cineractive;
    }

    void application_setup( )
    {
        if (app_ref != -2)
        {
            lua_rawgeti(lua_state, LUA_REGISTRYINDEX, app_ref);
            lua_getfield(lua_state, -1, "setup");
            if (lua_isnil(lua_state, -1))
            {
                lua_pop(lua_state, 2);
                return;
            }
            lua_rawgeti(lua_state, LUA_REGISTRYINDEX, app_ref);
            if (LUA_OK != lua_pcall(lua_state, 1, 0, 0))
            {
                scriptError(std::format("Error in setup: {}", lua_tostring(lua_state, -1)));
            }
        }
    }

    void application_update( )
    {
        if( common::Storage::instance().error )
        {
            return;
        }

        if( cineractive )
        {
            application_cineractiveUpdate();
        }
        else if (app_ref != -2)
        {
            lua_rawgeti(lua_state, LUA_REGISTRYINDEX, app_ref);
            lua_getfield(lua_state, -1, "update");
            if (lua_isnil(lua_state, -1))
            {
                lua_pop(lua_state, 2);
                return;
            }
            lua_rawgeti(lua_state, LUA_REGISTRYINDEX, app_ref);
            if (LUA_OK != lua_pcall(lua_state, 1, 0, 0))
            {
                scriptError(std::format("Error in update: {}", lua_tostring(lua_state, -1)));
            }
        }
    }

    void application_resume( )
    {
        if (app_ref != -2)
        {
            lua_rawgeti(lua_state, LUA_REGISTRYINDEX, app_ref);
            lua_getfield(lua_state, -1, "resume");
            if (lua_isnil(lua_state, -1))
            {
                lua_pop(lua_state, 2);
                return;
            }
            lua_rawgeti(lua_state, LUA_REGISTRYINDEX, app_ref);
            if (LUA_OK != lua_pcall(lua_state, 1, 0, 0))
            {
                scriptError(std::format("Error in resume: {}", lua_tostring(lua_state, -1)));
            }
        }
    }

    void application_cineractiveBegin( )
    {
        cineractive = true;
        if (app_ref != -2)
        {
            lua_rawgeti(lua_state, LUA_REGISTRYINDEX, app_ref);
            lua_getfield(lua_state, -1, "cineractiveBegin");
            if (lua_isnil(lua_state, -1))
            {
                lua_pop(lua_state, 2);
                return;
            }
            lua_rawgeti(lua_state, LUA_REGISTRYINDEX, app_ref);
            if (LUA_OK != lua_pcall(lua_state, 1, 0, 0))
            {
                scriptError(std::format("Error in cineractiveBegin: {}", lua_tostring(lua_state, -1)));
            }
        }
    }

    void application_cineractiveFinish( bool forced )
    {
        if (app_ref != -2)
        {
            lua_rawgeti(lua_state, LUA_REGISTRYINDEX, app_ref);
            lua_getfield(lua_state, -1, "cineractiveFinish");
            if (lua_isnil(lua_state, -1))
            {
                lua_pop(lua_state, 2);
                return;
            }
            lua_rawgeti(lua_state, LUA_REGISTRYINDEX, app_ref);
            if (LUA_OK != lua_pcall(lua_state, 1, 0, 0))
            {
                scriptError(std::format("Error in cineractiveFinish: {}", lua_tostring(lua_state, -1)));
            }
        }
        cineractive = false;
    }

    void application_register(lua_State* L)
    {
        lua_newtable(L);
        lua_pushcfunction(L, application_app_register);
        lua_setfield(L, -2, "register");
        lua_setglobal(L, "MMM");

        lua_state = L;
    }
}
