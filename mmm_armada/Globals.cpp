#include "Globals.h"
#include "PrintMessages.h"
#include "ScriptErrors.h"
#include "Debug_Internal.h"

namespace mmm
{
    namespace
    {
        int include(lua_State* L)
        {
            luaL_checktype(L, 1, LUA_TSTRING);
            std::string fn = lua_tostring(L, 1);
            mmm::include(fn);
            return 0;
        }

        int clear_print(lua_State*)
        {
            print::clear();
            return 0;
        }

        int global_print(lua_State* L)
        {
            print::add(lua_tostring(L, -1));
            return 0;
        }
    }

    void include(const std::string& fn)
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

    void globals_register(lua_State* L) noexcept
    {
        lua_pushcfunction(L, include);
        lua_setglobal(L, "include");
        lua_pushcfunction(L, clear_print);
        lua_setglobal(L, "clearPrint");
        lua_pushcfunction(L, global_print);
        lua_setglobal(L, "print");
    }
}