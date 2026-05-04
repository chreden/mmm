#include "TextInputHook.h"

namespace mmm
{
    TextInputHook::TextInputHook( const std::string& id, int table, int function, int argument, const std::string& pattern)
        : Hook(id, table, function, argument), pattern_(pattern)
    {
    }

    std::string TextInputHook::getPattern() const
    {
        return pattern_;
    }

    void TextInputHook::setPattern( const std::string& pattern )
    {
        pattern_ = pattern;
    }

    int TextInputHook::index(lua_State* L, const std::string& key) const
    {
        if (key == "pattern")
        {
            lua_pushstring(L, getPattern().c_str());
            return 1;
        }
        return Hook::index(L, key);
    }

    int TextInputHook::newindex(lua_State* L, const std::string& key)
    {
        if (key == "pattern")
        {
            setPattern(lua_tostring(L, 3));
            return 0;
        }
        return Hook::newindex(L, key);
    }
}
