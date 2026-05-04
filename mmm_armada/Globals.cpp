#include "Globals.h"
#include "PrintMessages.h"
#include "ScriptErrors.h"
#include "Debug_Internal.h"
#include "../external/lua/src/lauxlib.h"
#include <format>

namespace mmm
{
    namespace
    {
        int globals_print(lua_State* L)
        {
            if (lua_isstring(L, -1))
            {
                std::string str = lua_tostring(L, -1);
                print::add(str, DebuggerConnection::Type_Message);
            }
            return 0;
        }

        int globals_clear_print(lua_State*)
        {
            print::clear();
            return 0;
        }

        int globals_include_internal(lua_State* L)
        {
            std::string fn = lua_tostring(L, -1);
            globals_include(fn);
            return 0;
        }

        namespace
        {
            void copy_table(lua_State* L, int dest, int source_index)
            {
                // const int real_dest = (dest < 0 && dest > LUA_REGISTRYINDEX) ? (lua_gettop(L) + dest + 1) : dest;
                // const int real_source = (source_index < 0 && source_index > LUA_REGISTRYINDEX) ? (lua_gettop(L) + source_index + 1) : source_index;

                lua_pushvalue(L, source_index);
                int source = lua_gettop(L);

                lua_pushnil(L);
                while (lua_next(L, source) != 0)
                {
                    lua_pushvalue(L, -2);
                    lua_pushvalue(L, -2);
                    lua_rawset(L, dest);
                    lua_pop(L, 1);
                }
                lua_pop(L, 1);
            }
        }

        int class_call(lua_State* L)
        {
            int top = lua_gettop(L);

            lua_newtable(L);
            copy_table(L, lua_gettop(L), lua_upvalueindex(1));

            // Assign metatable
            lua_pushvalue(L, lua_upvalueindex(2));
            lua_setmetatable(L, -2);

            // Call 'constructor'
            int before_init = lua_gettop(L);
            lua_getfield(L, -1, "__init");
            if (lua_isfunction(L, -1))
            {
                lua_pushvalue(L, before_init);

                for (int i = 2; i <= top; ++i)
                {
                    lua_pushvalue(L, i);
                }

                if (LUA_OK != lua_pcall(L, 1 + std::max(0, (top - 1)), 0, 0))
                {
                    scriptError(std::format("Error in __init: {}", lua_tostring(L, -1)));
                }
            }

            lua_settop(L, before_init);
            return 1;
        }

        int class_call_inheritance(lua_State* L)
        {
            lua_newtable(L);
            
            int type = lua_type(L, lua_upvalueindex(1));

            lua_pushvalue(L, lua_upvalueindex(1));
            // Copy the 'global' object to the temporary table
            copy_table(L, 3, 4);

            // Copy base class to the 'global' object
            if (lua_gettop(L) == 4 && lua_istable(L, 2))
            {
                // copy_table(L, lua_gettop(L), 2);
                copy_table(L, 4, 2);
                // lua_pop(L, 1);
            }
            // Copy temporary back over the 'global'
            copy_table(L, 4, 3);

            return 0;
        }

        int globals_class(lua_State* L)
        {
            std::string name = lua_tostring(L, 1);
            const bool has_base = lua_gettop(L) == 2;

            // The 'global' class 
            lua_newtable(L);

            // Metatable for global object
            lua_newtable(L);
            lua_pushvalue(L, -2);
            lua_pushvalue(L, -2);
            lua_pushcclosure(L, class_call, 2);
            lua_setfield(L, -2, "__call");

            lua_setmetatable(L, -2);
            lua_pushvalue(L, -1);
            lua_setglobal(L, name.c_str());

            // Object to be returned that sets up inheritance
            lua_newtable(L);
            lua_newtable(L);
            lua_pushvalue(L, -3); // the 'global' object
            lua_pushcclosure(L, class_call_inheritance, 1);
            lua_setfield(L, -2, "__call");
            lua_setmetatable(L, -2);
            return 1;
        }
    }

    void globals_include(const std::string& fn)
    {
        common::Storage& storage = common::Storage::instance();
        common::FilePath oldPath = storage.path;
        try
        {
            std::string filename = storage.path.goTo(fn);

            lua_State* state = storage.mainLuaVM;
            luapack::FilePtr file = pack_getFile(storage.missionPack, filename.c_str());
            if (file)
            {
                if (luaL_dostring(state, file->getFileData()))
                {
                    scriptError(std::string("Error in include : ") + lua_tostring(state, -1));
                }
            }
            else
            {
                std::string finalFilePath;
                if (storage.modFolder.getFile(filename, finalFilePath))
                {
                    if (luaL_dofile(state, finalFilePath.c_str()))
                    {
                        scriptError(std::string("Error in include : ") + lua_tostring(state, -1));
                    }
                }
            }
        }
        catch (int)
        {
            scriptError("Error : invalid include specified");
        }

        //Go back to directory we were in?
        storage.path = oldPath;
    }

    void globals_register(lua_State* L)
    {
        lua_pushcfunction(L, globals_include_internal);
        lua_setglobal(L, "include");

        lua_pushcfunction(L, globals_print);
        lua_setglobal(L, "print");

        lua_pushcfunction(L, globals_clear_print);
        lua_setglobal(L, "clearPrint");

        lua_pushcfunction(L, globals_class);
        lua_setglobal(L, "class");
    }
}