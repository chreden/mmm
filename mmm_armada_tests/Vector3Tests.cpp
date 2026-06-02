#include "pch.h"
#include "CppUnitTest.h"
#include <external/lua/src/lua.hpp>
#include <mmm_armada/Vector3.h>
#include <mmm_armada/Matrix.h>
#include <Windows.h>
#include <format>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace mmm
{
    namespace tests
    {
        TEST_CLASS(Vector3)
        {
        public:
            TEST_METHOD(Add)
            {
                lua_State* L = luaL_newstate();
                vector_register(L);

                luaL_dostring(L, "vec = Vector(1, 2, 3) + Vector(1, 2, 3) return vec");
                Assert::AreEqual(LUA_TUSERDATA, lua_type(L, -1));
                luaL_dostring(L, "return vec.x");
                Assert::AreEqual(LUA_TNUMBER, lua_type(L, -1));
                Assert::AreEqual(2.0f, static_cast<float>(lua_tonumber(L, -1)));
                luaL_dostring(L, "return vec.y");
                Assert::AreEqual(LUA_TNUMBER, lua_type(L, -1));
                Assert::AreEqual(4.0f, static_cast<float>(lua_tonumber(L, -1)));
                luaL_dostring(L, "return vec.z");
                Assert::AreEqual(LUA_TNUMBER, lua_type(L, -1));
                Assert::AreEqual(6.0f, static_cast<float>(lua_tonumber(L, -1)));

                lua_close(L);
            }

            TEST_METHOD(Cross)
            {
                lua_State* L = luaL_newstate();
                vector_register(L);

                luaL_dostring(L, "vec = Vector(1, 2, 3):cross(Vector(4, 5, 6)) return vec");
                Assert::AreEqual(LUA_TUSERDATA, lua_type(L, -1));
                luaL_dostring(L, "return vec.x");
                Assert::AreEqual(LUA_TNUMBER, lua_type(L, -1));
                Assert::AreEqual(-5.0f, static_cast<float>(lua_tonumber(L, -1)));
                luaL_dostring(L, "return vec.y");
                Assert::AreEqual(LUA_TNUMBER, lua_type(L, -1));
                Assert::AreEqual(6.0f, static_cast<float>(lua_tonumber(L, -1)));
                luaL_dostring(L, "return vec.z");
                Assert::AreEqual(LUA_TNUMBER, lua_type(L, -1));
                Assert::AreEqual(-3.0f, static_cast<float>(lua_tonumber(L, -1)));

                lua_close(L);
            }

            TEST_METHOD(Divide)
            {
                lua_State* L = luaL_newstate();
                vector_register(L);

                luaL_dostring(L, "vec = Vector(1, 2, 3) / 2.0 return vec");
                Assert::AreEqual(LUA_TUSERDATA, lua_type(L, -1));
                luaL_dostring(L, "return vec.x");
                Assert::AreEqual(LUA_TNUMBER, lua_type(L, -1));
                Assert::AreEqual(0.5f, static_cast<float>(lua_tonumber(L, -1)));
                luaL_dostring(L, "return vec.y");
                Assert::AreEqual(LUA_TNUMBER, lua_type(L, -1));
                Assert::AreEqual(1.0f, static_cast<float>(lua_tonumber(L, -1)));
                luaL_dostring(L, "return vec.z");
                Assert::AreEqual(LUA_TNUMBER, lua_type(L, -1));
                Assert::AreEqual(1.5f, static_cast<float>(lua_tonumber(L, -1)));

                lua_close(L);
            }

            TEST_METHOD(Dot)
            {
                lua_State* L = luaL_newstate();
                vector_register(L);

                luaL_dostring(L, "return Vector(1, 2, 3):dot(Vector(4, 5, 6))");
                Assert::AreEqual(LUA_TNUMBER, lua_type(L, -1));
                Assert::AreEqual(32.0f, static_cast<float>(lua_tonumber(L, -1)));

                lua_close(L);
            }

            TEST_METHOD(Length)
            {
                lua_State* L = luaL_newstate();
                vector_register(L);

                luaL_dostring(L, "return Vector(1, 2, 3).length");
                Assert::AreEqual(LUA_TNUMBER, lua_type(L, -1));
                Assert::AreEqual(3.7416573867739413855837487323165f, static_cast<float>(lua_tonumber(L, -1)));

                lua_close(L);
            }

            TEST_METHOD(LengthSquared)
            {
                lua_State* L = luaL_newstate();
                vector_register(L);

                luaL_dostring(L, "return Vector(1, 2, 3).lengthSquared");
                Assert::AreEqual(LUA_TNUMBER, lua_type(L, -1));
                Assert::AreEqual(14.0f, static_cast<float>(lua_tonumber(L, -1)));

                lua_close(L);
            }

            TEST_METHOD(Lerp)
            {
                lua_State* L = luaL_newstate();
                vector_register(L);

                luaL_dostring(L, "vec = Vector(1, 2, 3):lerp(Vector(4, 5, 6), 0.5) return vec");
                Assert::AreEqual(LUA_TUSERDATA, lua_type(L, -1));
                luaL_dostring(L, "return vec.x");
                Assert::AreEqual(LUA_TNUMBER, lua_type(L, -1));
                Assert::AreEqual(2.5f, static_cast<float>(lua_tonumber(L, -1)));
                luaL_dostring(L, "return vec.y");
                Assert::AreEqual(LUA_TNUMBER, lua_type(L, -1));
                Assert::AreEqual(3.5f, static_cast<float>(lua_tonumber(L, -1)));
                luaL_dostring(L, "return vec.z");
                Assert::AreEqual(LUA_TNUMBER, lua_type(L, -1));
                Assert::AreEqual(4.5f, static_cast<float>(lua_tonumber(L, -1)));

                lua_close(L);
            }

            TEST_METHOD(MultiplyMatrix)
            {
                lua_State* L = luaL_newstate();
                vector_register(L);
                matrix_register(L);

                luaL_dostring(L, "vec = Vector(1, 2, 3) * Matrix.scaling(2.0) return vec");
                Assert::AreEqual(LUA_TUSERDATA, lua_type(L, -1));
                luaL_dostring(L, "return vec.x");
                Assert::AreEqual(LUA_TNUMBER, lua_type(L, -1));
                Assert::AreEqual(2.0f, static_cast<float>(lua_tonumber(L, -1)));
                luaL_dostring(L, "return vec.y");
                Assert::AreEqual(LUA_TNUMBER, lua_type(L, -1));
                Assert::AreEqual(4.0f, static_cast<float>(lua_tonumber(L, -1)));
                luaL_dostring(L, "return vec.z");
                Assert::AreEqual(LUA_TNUMBER, lua_type(L, -1));
                Assert::AreEqual(6.0f, static_cast<float>(lua_tonumber(L, -1)));

                lua_close(L);
            }

            TEST_METHOD(MultiplyScalar)
            {
                lua_State* L = luaL_newstate();
                vector_register(L);

                luaL_dostring(L, "vec = Vector(1, 2, 3) * 2.0 return vec");
                Assert::AreEqual(LUA_TUSERDATA, lua_type(L, -1));
                luaL_dostring(L, "return vec.x");
                Assert::AreEqual(LUA_TNUMBER, lua_type(L, -1));
                Assert::AreEqual(2.0f, static_cast<float>(lua_tonumber(L, -1)));
                luaL_dostring(L, "return vec.y");
                Assert::AreEqual(LUA_TNUMBER, lua_type(L, -1));
                Assert::AreEqual(4.0f, static_cast<float>(lua_tonumber(L, -1)));
                luaL_dostring(L, "return vec.z");
                Assert::AreEqual(LUA_TNUMBER, lua_type(L, -1));
                Assert::AreEqual(6.0f, static_cast<float>(lua_tonumber(L, -1)));

                lua_close(L);
            }

            TEST_METHOD(Normalize)
            {
                lua_State* L = luaL_newstate();
                vector_register(L);

                luaL_dostring(L, "vec = Vector(1, 1, 1):normalize() return vec");
                Assert::AreEqual(LUA_TUSERDATA, lua_type(L, -1));
                luaL_dostring(L, "return vec.x");
                Assert::AreEqual(LUA_TNUMBER, lua_type(L, -1));
                Assert::AreEqual(0.57735f, static_cast<float>(lua_tonumber(L, -1)), 0.1f);
                luaL_dostring(L, "return vec.y");
                Assert::AreEqual(LUA_TNUMBER, lua_type(L, -1));
                Assert::AreEqual(0.57735f, static_cast<float>(lua_tonumber(L, -1)), 0.1f);
                luaL_dostring(L, "return vec.z");
                Assert::AreEqual(LUA_TNUMBER, lua_type(L, -1));
                Assert::AreEqual(0.57735f, static_cast<float>(lua_tonumber(L, -1)), 0.1f);

                lua_close(L);
            }

            TEST_METHOD(XYZ)
            {
                lua_State* L = luaL_newstate();
                vector_register(L);

                luaL_dostring(L, "vec = Vector(1, 2, 3)");

                luaL_dostring(L, "return vec.x");
                Assert::AreEqual(LUA_TNUMBER, lua_type(L, -1));
                Assert::AreEqual(1.0f, static_cast<float>(lua_tonumber(L, -1)));

                luaL_dostring(L, "return vec.y");
                Assert::AreEqual(LUA_TNUMBER, lua_type(L, -1));
                Assert::AreEqual(2.0f, static_cast<float>(lua_tonumber(L, -1)));

                luaL_dostring(L, "return vec.z");
                Assert::AreEqual(LUA_TNUMBER, lua_type(L, -1));
                Assert::AreEqual(3.0f, static_cast<float>(lua_tonumber(L, -1)));

                lua_close(L);
            }

            TEST_METHOD(Performance)
            {
                lua_State* L = luaL_newstate();
                vector_register(L);

                luaL_dostring(L, "vec = Vector()");

                DWORD start = GetTickCount();
                for (int i = 0; i < 1000000; ++i)
                {
                    luaL_dostring(L, "return vec.z");
                    lua_pop(L, 1);
                }
                DWORD end = GetTickCount();
                Logger::WriteMessage(std::format("Time: {}", (end - start) / 1000.0f).c_str());
            }

            TEST_METHOD(Subtract)
            {
                lua_State* L = luaL_newstate();
                vector_register(L);

                luaL_dostring(L, "vec = Vector(1, 2, 3) - Vector(3, 2, 1) return vec");
                Assert::AreEqual(LUA_TUSERDATA, lua_type(L, -1));
                luaL_dostring(L, "return vec.x");
                Assert::AreEqual(LUA_TNUMBER, lua_type(L, -1));
                Assert::AreEqual(-2.0f, static_cast<float>(lua_tonumber(L, -1)));
                luaL_dostring(L, "return vec.y");
                Assert::AreEqual(LUA_TNUMBER, lua_type(L, -1));
                Assert::AreEqual(0.0f, static_cast<float>(lua_tonumber(L, -1)));
                luaL_dostring(L, "return vec.z");
                Assert::AreEqual(LUA_TNUMBER, lua_type(L, -1));
                Assert::AreEqual(2.0f, static_cast<float>(lua_tonumber(L, -1)));

                lua_close(L);
            }
        };
    }
}
