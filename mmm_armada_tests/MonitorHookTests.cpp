#include "pch.h"
#include "CppUnitTest.h"
#include <external/lua/src/lua.hpp>
#include <mmm_armada/Monitor.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace mmm
{
    namespace tests
    {
        TEST_CLASS(MonitorHook)
        {
        public:
            TEST_METHOD(TypeEnum)
            {
                lua_State* L = luaL_newstate();
                mmm::monitorhook_register(L);

                luaL_dostring(L, "return MonitorHook.Type.OnTrue");
                Assert::AreEqual(LUA_TNUMBER, lua_type(L, -1));
                Assert::AreEqual(0.0f, static_cast<float>(lua_tonumber(L, -1)));

                luaL_dostring(L, "return MonitorHook.Type.OnFalse");
                Assert::AreEqual(LUA_TNUMBER, lua_type(L, -1));
                Assert::AreEqual(1.0f, static_cast<float>(lua_tonumber(L, -1)));

                luaL_dostring(L, "return MonitorHook.Type.WhileTrue");
                Assert::AreEqual(LUA_TNUMBER, lua_type(L, -1));
                Assert::AreEqual(2.0f, static_cast<float>(lua_tonumber(L, -1)));

                luaL_dostring(L, "return MonitorHook.Type.WhileFalse");
                Assert::AreEqual(LUA_TNUMBER, lua_type(L, -1));
                Assert::AreEqual(3.0f, static_cast<float>(lua_tonumber(L, -1)));

                luaL_dostring(L, "return MonitorHook.Type.OnStop");
                Assert::AreEqual(LUA_TNUMBER, lua_type(L, -1));
                Assert::AreEqual(4.0f, static_cast<float>(lua_tonumber(L, -1)));

                lua_close(L);
            }
        };
    }
}
