#include "Application.h"
#include "ScriptErrors.h"

namespace mmm
{
    namespace
    {
        int  app_table_index{ 0 };
        bool cineractive;

        struct PreserveStack
        {
            explicit PreserveStack(lua_State* L) noexcept
                : top(lua_gettop(L)), L(L)
            {
            }

            ~PreserveStack()
            {
                lua_settop(L, top);
            }

            PreserveStack(const PreserveStack&) = delete;
            PreserveStack(PreserveStack&&) = delete;
            PreserveStack& operator=(const PreserveStack&) = delete;
            PreserveStack& operator=(PreserveStack&&) = delete;

            lua_State* L;
            int top{ 0 };
        };

        bool get_application(lua_State* L)
        {
            lua_rawgeti(L, LUA_REGISTRYINDEX, app_table_index);
            lua_getfield(L, -1, "app");
            if (lua_type(L, -1) == LUA_TUSERDATA || lua_type(L, -1) == LUA_TTABLE)
            {
                lua_remove(L, -2);
                return true;
            }
            lua_pop(L, 2);
            return false;
        }

        void application_cineractiveUpdate()
        {
            lua_State* L = common::Storage::instance().mainLuaVM;
            PreserveStack stack{ L };
            if (get_application(L))
            {
                lua_getfield(L, -1, "cineractiveUpdate");
                if (lua_type(L, -1) == LUA_TFUNCTION)
                {
                    lua_pushvalue(L, -2);
                    if (lua_pcall(L, 1, 0, 0))
                    {
                        scriptError(std::string("Error in cineractiveUpdate : ") + lua_tostring(L, -1));
                    }
                }
            }
        }

        int application_app_register(lua_State* L) noexcept
        {
            lua_rawgeti(L, LUA_REGISTRYINDEX, app_table_index);
            lua_pushvalue(L, 1);
            lua_setfield(L, -2, "app");
            return 0;
        }
    }

    bool application_isCineractive() noexcept
    {
        return cineractive;
    }

    void application_setup( )
    {
        lua_State* L = common::Storage::instance().mainLuaVM;
        PreserveStack stack{ L };
        if (get_application(L))
        {
            lua_getfield(L, -1, "setup");
            if (lua_type(L, -1) == LUA_TFUNCTION)
            {
                lua_pushvalue(L, -2);
                if (lua_pcall(L, 1, 0, 0))
                {
                    scriptError(std::string("Error in setup : ") + lua_tostring(L, -1));
                }
            }
        }
    }

    void application_update( )
    {
        if( common::Storage::instance().error )
        {
            return;
        }

        lua_State* L = common::Storage::instance().mainLuaVM;
        PreserveStack stack{ L };
        if( cineractive )
        {
            application_cineractiveUpdate();
        }
        else if (get_application(L))
        {
            lua_getfield(L, -1, "update");
            if (lua_type(L, -1) == LUA_TFUNCTION)
            {
                lua_pushvalue(L, -2);
                if (lua_pcall(L, 1, 0, 0))
                {
                    scriptError(std::string("Error in update : ") + lua_tostring(L, -1));
                }
            }
        }
    }

    void application_resume( )
    {
        lua_State* L = common::Storage::instance().mainLuaVM;
        PreserveStack stack{ L };
        if (get_application(L))
        {
            lua_getfield(L, -1, "resume");
            if (lua_type(L, -1) == LUA_TFUNCTION)
            {
                lua_pushvalue(L, -2);
                if (lua_pcall(L, 1, 0, 0))
                {
                    scriptError(std::string("Error in resume : ") + lua_tostring(L, -1));
                }
            }
        }
    }

    void application_cineractiveBegin( )
    {
        cineractive = true;
        lua_State* L = common::Storage::instance().mainLuaVM;
        PreserveStack stack{ L };
        if (get_application(L))
        {
            lua_getfield(L, -1, "cineractiveBegin");
            if (lua_type(L, -1) == LUA_TFUNCTION)
            {
                lua_pushvalue(L, -2);
                if (lua_pcall(L, 1, 0, 0))
                {
                    scriptError(std::string("Error in cineractiveBegin : ") + lua_tostring(L, -1));
                }
            }
        }
    }

    void application_cineractiveFinish( bool forced )
    {
        lua_State* L = common::Storage::instance().mainLuaVM;
        PreserveStack stack{ L };
        if (get_application(L))
        {
            lua_getfield(L, -1, "cineractiveFinish");
            if (lua_type(L, -1) == LUA_TFUNCTION)
            {
                lua_pushvalue(L, -2);
                lua_pushboolean(L, forced);
                if (lua_pcall(L, 2, 0, 0))
                {
                    scriptError(std::string("Error in cineractiveFinish : ") + lua_tostring(L, -1));
                }
            }
        }
        cineractive = false;
    }

    void application_register(lua_State* L) noexcept
    {
        lua_newtable(L);
        app_table_index = luaL_ref(L, LUA_REGISTRYINDEX);

        lua_newtable(L);
        lua_pushcfunction(L, application_app_register);
        lua_setfield(L, -2, "register");
        lua_setglobal(L, "MMM");
    }
}
