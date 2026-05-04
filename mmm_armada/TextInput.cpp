#include "TextInput.h"
#include "ScriptErrors.h"
#include "TextInputHook.h"
#include "LuaBinding.h"
#include <format>

namespace mmm
{
    namespace
    {
        TextInput textInput;
        const std::size_t Address_IsActive = 0x0065f120;
        const std::size_t Address_GetString = 0x0065e860;
        const std::size_t Address_SetPrompt = 0x0065e730;

        int textinput_hook(lua_State* L)
        {
            if (lua_gettop(L) == 6)
            {
                std::string pattern = lua_tostring(L, 6);
                lua_pop(L, 1);
                int argument = luaL_ref(L, LUA_REGISTRYINDEX);
                int function = luaL_ref(L, LUA_REGISTRYINDEX);
                int table = luaL_ref(L, LUA_REGISTRYINDEX);
                textInput.hook(lua_tostring(L, 2), table, function, argument, pattern);
            }
            
            int argument = luaL_ref(L, LUA_REGISTRYINDEX);
            int function = luaL_ref(L, LUA_REGISTRYINDEX);
            int table = luaL_ref(L, LUA_REGISTRYINDEX);
            lua_pushboolean(L, textInput.hook(lua_tostring(L, 2), table, function, argument));
            return 1;
        }

        int textinput_unhook(lua_State* L)
        {
            if (lua_type(L, 2) == LUA_TSTRING)
            {
                lua_pushboolean(L, textInput.unhook(lua_tostring(L, 2)));
                return 1;
            }
            lua_pushboolean(L, textInput.unhook(get_userdata<std::shared_ptr<Hook>>(L, 2)));
            return 1;
        }

        int textinput_index(lua_State* L)
        {
            const std::string key = lua_tostring(L, 2);

            if (key == "active")
            {
                lua_pushboolean(L, textInput.getActive());
                return 1;
            }
            else if (key == "hook")
            {
                lua_pushcfunction(L, textinput_hook);
                return 1;
            }
            else if (key == "hooks")
            {
                return textInput.getHooks(L);
            }
            else if (key == "prompt")
            {
                lua_pushstring(L, textInput.getPrompt().c_str());
                return 1;
            }
            else if (key == "text")
            {
                lua_pushstring(L, textInput.getText().c_str());
                return 1;
            }
            else if (key == "unhook")
            {
                lua_pushcfunction(L, textinput_unhook);
                return 1;
            }
            return 0;
        }

        int textinput_newindex(lua_State* L)
        {
            const std::string key = lua_tostring(L, 2);
            if (key == "prompt")
            {
                textInput.setPrompt(lua_tostring(L, 3));
                return 0;
            }
            return 0;
        }
    }

    void TextInput::update()
    {
        common::Storage& storage(common::Storage::instance());
        lua_State* L = storage.mainLuaVM;

        void* context = memory_function< void* (*)() >(Address_IsActive)();
        //Check to see if anything has changed.
        bool active = context != 0;

        if(active)
        {
            //Capture string here.
            previousString_ = memory_function< char* (*)(void*) >(Address_GetString)(context);
        }
        else if(active != previousActive_)
        {
            // TODO: Reinstate
            lua_getglobal(L, "string");
            lua_getfield(L, -1, "find");
            int findFunction = luaL_ref(L, LUA_REGISTRYINDEX);
            lua_pop(L, 1);

            auto hookCopy = hooks_;
            for (const auto& [key, hook] : hookCopy)
            {
                if (!hook->getPattern().empty() && findFunction != LUA_NOREF)
                {
                    //The hook has a pattern that needs to be matched -
                    //if it passes then we will use it, otherwise we just
                    //bail out.
                    lua_rawgeti(L, LUA_REGISTRYINDEX, findFunction);
                    lua_pushstring(L, previousString_.c_str());
                    lua_pushstring(L, hook->getPattern().c_str());
                    if (LUA_OK == lua_pcall(L, 2, 1, 0))
                    {
                        if (lua_type(L, -1) == LUA_TNIL)
                        {
                            continue;
                        }
                    }
                    else
                    {
                        scriptError(std::format("Error in TextInput hook ({}): {}", key, lua_tostring(L, -1)).c_str());
                    }
                    lua_pop(L, 1);
                }

                int arguments = 2;
                lua_rawgeti(L, LUA_REGISTRYINDEX, hook->function());
                if (hook->table() != LUA_NOREF)
                {
                    lua_rawgeti(L, LUA_REGISTRYINDEX, hook->table());
                    ++arguments;
                }
                lua_pushstring(L, previousString_.c_str());
                hook_new(L, hook);
                if (LUA_OK != lua_pcall(L, arguments, 0, 0))
                {
                    scriptError(std::format("Error in TextInput hook ({}): {}", key, lua_tostring(L, -1)).c_str());
                    lua_pop(L, 1);
                }
            }

            /*
            //Used with pattern matching hooks.
            luabind::object findFunction;
            luabind::object stringObject = luabind::globals(common::Storage::instance().mainLuaVM)["string"];
            if(stringObject.is_valid())
            {
                findFunction = stringObject["find"];
            }

            auto hookCopy = hooks_;
            for(auto iter = hookCopy.begin();
                 iter != hookCopy.end();
                 ++iter)
            {
                try
                {
                    TextInputHookPtr hook = iter->second;

                    if(!hook->getPattern().empty() && findFunction.is_valid())
                    {
                        //The hook has a pattern that needs to be matched -
                        //if it passes then we will use it, otherwise we just
                        //bail out.
                        luabind::object found = luabind::call_function<luabind::object>(findFunction, previousString_, hook->getPattern());
                        if(luabind::type(found) == LUA_TNIL) 
                        {
                            continue;
                        }
                    }

                    if(hook->getTable().is_valid() && 
                        luabind::type(hook->getTable()) != LUA_TNIL)
                    {
                        luabind::call_function<void>(hook->getFunction(), hook->getTable(), previousString_, hook);
                    }
                    else
                    {
                        luabind::call_function<void>(hook->getFunction(), previousString_, hook);
                    }
                }
                catch(const luabind::error&)
                {
                    scriptError(std::string("Error in TextInput hook (" + iter->first + "): ") + lua_tostring(state, -1));
                }
            }*/
        }

        previousActive_ = active;
    }

    bool TextInput::getActive() const
    {
        return memory_function< void* (*)() >(Address_IsActive)() != nullptr;
    }

    std::string TextInput::getPrompt() const
    {
        return "";
    }

    std::string TextInput::getText() const
    {
        void* context = memory_function< void* (*)() >(Address_IsActive)();
        if(context)
        {
            return memory_function< char* (*)(void*) >(Address_GetString)(context);
        }
        return "";
    }

    void TextInput::setPrompt(const std::string& prompt)
    {
        void* context = memory_function< void* (*)() >(Address_IsActive)();
        if(context)
        {
            memory_function< void (*)(void*,char*) >(Address_SetPrompt 
               )(context, const_cast<char*>(prompt.c_str()));
        }
    }

    bool TextInput::hook(const std::string& id, int table, int function, int argument)
    {
        return hook(id, table, function, argument, "");
    }

    bool TextInput::hook(const std::string& id, int table, int function, int argument, const std::string& pattern)
    {
        if(hooks_.find(id) != hooks_.end())
        {
            return false;
        }
        hooks_[id] = std::make_shared<TextInputHook>(id, table, function, argument, pattern);
        return true;
    }

    bool TextInput::unhook(const std::string& id)
    {
        auto iter = hooks_.find(id);
        if(iter != hooks_.end())
        {
            hooks_.erase(iter);
            return true;
        }
        return false;
    }

    bool TextInput::unhook(const std::shared_ptr<Hook>& hook)
    {
        if(!hook)
        {
            return false;
        }

        auto iter = hooks_.find(hook->id());
        if(iter == hooks_.end())
        {
            return false;
        }

        hooks_.erase(iter);
        return true;
    }

    int TextInput::getHooks(lua_State* L) const
    {
        lua_newtable(L);
        for (auto iter = hooks_.begin(); iter != hooks_.end(); ++iter)
        {
            hook_new(L, iter->second);
            lua_setfield(L, -2, iter->first.c_str());
        }
        return 1;
    }

    void textinput_update()
    {
        textInput.update();
    }

    void textinput_register(lua_State* L)
    {
        lua_newtable(L);
        create_metatable(L,
            {
                { "__index", textinput_index },
                { "__newindex", textinput_newindex }
            });
        lua_setglobal(L, "TextInput");
    }
}