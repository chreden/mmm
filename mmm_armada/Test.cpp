#include "Test.h"
#include "PrintMessages.h"
#include "DebuggerConnection.h"
#include <format>
#include "LuaBinding.h"

namespace mmm
{
    namespace
    {
        Test test;

        int test_add(lua_State* L)
        {
            std::string name = lua_tostring(L, 2);
            int function = luaL_ref(L, LUA_REGISTRYINDEX);
            int table = luaL_ref(L, LUA_REGISTRYINDEX);
            test.add(name, table, function);
            return 0;
        }

        int test_isfalse(lua_State* L)
        {
            test.isFalse(lua_toboolean(L, 2), lua_tostring(L, 3));
            return 0;
        }

        int test_istrue(lua_State* L)
        {
            test.isTrue(lua_toboolean(L, 2), lua_tostring(L, 3));
            return 0;
        }

        int test_run(lua_State* L)
        {
            test.runAll(L);
            return 0;
        }

        int test_index(lua_State* L)
        {
            const std::string key = lua_tostring(L, 2);
            if (key == "add")
            {
                lua_pushcfunction(L, test_add);
                return 1;
            }
            else if (key == "isFalse")
            {
                lua_pushcfunction(L, test_isfalse);
                return 1;
            }
            else if (key == "isTrue")
            {
                lua_pushcfunction(L, test_istrue);
                return 1;
            }
            else if (key == "run")
            {
                lua_pushcfunction(L, test_run);
                return 1;
            }
            return 0;
        }
    }

    void Test::isTrue(bool condition, const std::string& message) const
    {
        if(!condition)
        {
            throw AssertionFailureException(message);
        }
    }

    void Test::isFalse(bool condition, const std::string& message) const
    {
        isTrue(!condition, message);
    }

    void Test::add(const std::string& name, int table, int function)
    {
        tests_.push_back(TestEntry(name, table, function));
    }

    void Test::runAll(lua_State* L)
    {
        for (const auto& test : tests_)
        {
            test.run(L);
        }
    }

    Test::TestEntry::TestEntry(const std::string& name, int table, int function)
        : name_(name), table_(table), function_(function)
    {
    }

    bool Test::TestEntry::call(lua_State* L) const
    {
        lua_rawgeti(L, LUA_REGISTRYINDEX, function_);
        lua_rawgeti(L, LUA_REGISTRYINDEX, table_);
        if (lua_isnil(L, -1))
        {
            lua_pop(L, 1);
            return LUA_OK == lua_pcall(L, 0, 0, 0);
        }
        return LUA_OK == lua_pcall(L, 1, 0, 0);
    }

    void Test::TestEntry::run(lua_State* L) const
    {
        if (call(L))
        {
            print::add(std::format("Pass:{}", name_), DebuggerConnection::Type_Test);
        }
        else
        {
            std::string actualError = lua_tostring(L, -1);
            std::size_t startIndex = actualError.find_first_of('\'');
            std::size_t endIndex = actualError.find_last_of('\'');

            if (!(startIndex == actualError.npos || endIndex == actualError.npos))
            {
                actualError = actualError.substr(startIndex + 1, endIndex - startIndex - 1);
            }

            print::add("Fail:" + name_ + ":" + actualError, DebuggerConnection::Type_Test);
        }
    }

    void test_register(lua_State* L)
    {
        lua_newtable(L);
        create_metatable(L,
            {
                { "__index", test_index }
            });
        lua_setglobal(L, "Test");
    }
}
