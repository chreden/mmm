#include "pch.h"
#include "CppUnitTest.h"
#include <external/lua/src/lua.hpp>
#include <mmm_armada/Monitor.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace mmmarmadatests
{
    TEST_CLASS(Monitor)
    {
    public:
        TEST_METHOD(RelationEnum)
        {
            lua_State* L = luaL_newstate();
            mmm::monitor_register(L);

            luaL_dostring(L, "return Monitor.Relation.Enemy");
            Assert::AreEqual(LUA_TNUMBER, lua_type(L, -1));
            Assert::AreEqual(0.0f, static_cast<float>(lua_tonumber(L, -1)));

            luaL_dostring(L, "return Monitor.Relation.Neutral");
            Assert::AreEqual(LUA_TNUMBER, lua_type(L, -1));
            Assert::AreEqual(1.0f, static_cast<float>(lua_tonumber(L, -1)));

            luaL_dostring(L, "return Monitor.Relation.Ally");
            Assert::AreEqual(LUA_TNUMBER, lua_type(L, -1));
            Assert::AreEqual(2.0f, static_cast<float>(lua_tonumber(L, -1)));

            lua_close(L);
        }

        TEST_METHOD(HookCalledNoTable)
        {
            lua_State* L = luaL_newstate();
            mmm::monitor_register(L);
            mmm::hook_register(L);
            mmm::monitorhook_register(L);

            luaL_dostring(L, "condition_arg = nil");
            luaL_dostring(L, "hook_arg = nil");
            luaL_dostring(L, "function condition(monitor, arg) condition_arg = arg return true end");
            luaL_dostring(L, "function test_hook(monitor, hook) hook_arg = hook.argument end");
            luaL_dostring(L, "x = Monitor(\"id\", false, nil, condition, \"condition\")");
            luaL_dostring(L, "x:hook(\"id\", MonitorHook.Type.OnTrue, nil, test_hook, \"hook\")");

            mmm::Monitor::update();

            luaL_dostring(L, "return condition_arg");
            Assert::AreEqual(LUA_TSTRING, lua_type(L, -1));
            Assert::AreEqual(std::string("condition"), std::string(lua_tostring(L, -1)));

            luaL_dostring(L, "return hook_arg");
            Assert::AreEqual(LUA_TSTRING, lua_type(L, -1));
            Assert::AreEqual(std::string("hook"), std::string(lua_tostring(L, -1)));
        }
    };
}
