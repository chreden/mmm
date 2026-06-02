#include "pch.h"
#include "CppUnitTest.h"
#include <external/lua/src/lua.hpp>
#include <mmm_armada/Vector3.h>
#include <mmm_armada/Matrix.h>
#include <mmm_armada/LuaBinding.h>
#include <Windows.h>
#include <format>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Microsoft
{
    namespace VisualStudio
    {
        namespace CppUnitTestFramework
        {
            template <>
            std::wstring ToString(const mmm::Matrix& m)
            {
                return std::format(L"{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{}",
                    m.get(0, 0), m.get(0, 1), m.get(0, 2), m.get(0, 3),
                    m.get(1, 0), m.get(1, 1), m.get(1, 2), m.get(1, 3),
                    m.get(2, 0), m.get(2, 1), m.get(2, 2), m.get(2, 3),
                    m.get(3, 0), m.get(3, 1), m.get(3, 2), m.get(3, 3));
            }

            template <>
            std::wstring ToString(const mmm::Vector3& v)
            {
                return std::format(L"{},{},{}", v.x, v.y, v.z);
            }
        }
    }
}

namespace mmm
{
    namespace tests
    {
        TEST_CLASS(Matrix)
        {
        public:
            TEST_METHOD(Get)
            {
                lua_State* L = luaL_newstate();
                matrix_register(L);

                luaL_dostring(L, "mat = Matrix.rotationX(2) return mat:get(2, 2)");
                Assert::AreEqual(LUA_TNUMBER, lua_type(L, -1));
                Assert::AreEqual(-0.416146845f, static_cast<float>(lua_tonumber(L, -1)));

                lua_close(L);
            }

            TEST_METHOD(MultiplyMatrix)
            {
                lua_State* L = luaL_newstate();
                matrix_register(L);

                luaL_dostring(L, "return Matrix.rotationX(2) * Matrix.rotationY(3)");
                const auto matrix = get_userdata<mmm::Matrix>(L, -1);
                Assert::AreEqual(mmm::Matrix::rotationX(2) * mmm::Matrix::rotationY(3), matrix);

                lua_close(L);
            }

            TEST_METHOD(MultiplyVector)
            {
                lua_State* L = luaL_newstate();
                matrix_register(L);
                vector_register(L);

                luaL_dostring(L, "return Matrix.rotationX(2) * Vector(1, 2, 3)");
                const auto vec = get_userdata<mmm::Vector3>(L, -1);
                Assert::AreEqual(mmm::Matrix::rotationX(2) * mmm::Vector3(1, 2, 3), vec);

                lua_close(L);
            }

            TEST_METHOD(RotationX)
            {
                lua_State* L = luaL_newstate();
                matrix_register(L);

                luaL_dostring(L, "return Matrix.rotationX(2)");
                const auto matrix = get_userdata<mmm::Matrix>(L, -1);
                Assert::AreEqual(mmm::Matrix::rotationX(2), matrix);

                lua_close(L);
            }

            TEST_METHOD(RotationY)
            {
                lua_State* L = luaL_newstate();
                matrix_register(L);

                luaL_dostring(L, "return Matrix.rotationY(2)");
                const auto matrix = get_userdata<mmm::Matrix>(L, -1);
                Assert::AreEqual(mmm::Matrix::rotationY(2), matrix);

                lua_close(L);
            }

            TEST_METHOD(RotationZ)
            {
                lua_State* L = luaL_newstate();
                matrix_register(L);

                luaL_dostring(L, "return Matrix.rotationZ(2)");
                const auto matrix = get_userdata<mmm::Matrix>(L, -1);
                Assert::AreEqual(mmm::Matrix::rotationZ(2), matrix);

                lua_close(L);
            }

            TEST_METHOD(Rotation)
            {
                lua_State* L = luaL_newstate();
                matrix_register(L);

                luaL_dostring(L, "return Matrix.rotation(2, 3, 4)");
                const auto matrix = get_userdata<mmm::Matrix>(L, -1);
                Assert::AreEqual(mmm::Matrix::rotation(2, 3, 4), matrix);

                lua_close(L);
            }

            TEST_METHOD(RotationVector)
            {
                lua_State* L = luaL_newstate();
                matrix_register(L);
                vector_register(L);

                luaL_dostring(L, "return Matrix.rotation(Vector(2, 3, 4))");
                const auto matrix = get_userdata<mmm::Matrix>(L, -1);
                Assert::AreEqual(mmm::Matrix::rotation(Vector3(2, 3, 4)), matrix);

                lua_close(L);
            }

            TEST_METHOD(Translation)
            {
                lua_State* L = luaL_newstate();
                matrix_register(L);

                luaL_dostring(L, "return Matrix.translation(2, 3, 4)");
                const auto matrix = get_userdata<mmm::Matrix>(L, -1);
                Assert::AreEqual(mmm::Matrix::translation(2, 3, 4), matrix);

                lua_close(L);
            }

            TEST_METHOD(TranslationVector)
            {
                lua_State* L = luaL_newstate();
                matrix_register(L);
                vector_register(L);

                luaL_dostring(L, "return Matrix.translation(Vector(2, 3, 4))");
                const auto matrix = get_userdata<mmm::Matrix>(L, -1);
                Assert::AreEqual(mmm::Matrix::translation(Vector3(2, 3, 4)), matrix);

                lua_close(L);
            }

            TEST_METHOD(Transpose)
            {
                lua_State* L = luaL_newstate();
                matrix_register(L);

                luaL_dostring(L, "return Matrix.rotation(2, 3, 4):transpose()");
                const auto matrix = get_userdata<mmm::Matrix>(L, -1);
                Assert::AreEqual(mmm::Matrix::rotation(2, 3, 4).transpose(), matrix);

                lua_close(L);
            }

            TEST_METHOD(Scaling)
            {
                lua_State* L = luaL_newstate();
                matrix_register(L);

                luaL_dostring(L, "return Matrix.scaling(2, 3, 4)");
                const auto matrix = get_userdata<mmm::Matrix>(L, -1);
                Assert::AreEqual(mmm::Matrix::scaling(2, 3, 4), matrix);

                lua_close(L);
            }

            TEST_METHOD(ScalingScalar)
            {
                lua_State* L = luaL_newstate();
                matrix_register(L);

                luaL_dostring(L, "return Matrix.scaling(5)");
                const auto matrix = get_userdata<mmm::Matrix>(L, -1);
                Assert::AreEqual(mmm::Matrix::scaling(5.0f), matrix);

                lua_close(L);
            }

            TEST_METHOD(ScalingVector)
            {
                lua_State* L = luaL_newstate();
                matrix_register(L);
                vector_register(L);

                luaL_dostring(L, "return Matrix.scaling(Vector(2, 3, 4))");
                const auto matrix = get_userdata<mmm::Matrix>(L, -1);
                Assert::AreEqual(mmm::Matrix::scaling(Vector3(2, 3, 4)), matrix);

                lua_close(L);
            }

            TEST_METHOD(Set)
            {
                lua_State* L = luaL_newstate();
                matrix_register(L);

                luaL_dostring(L, "mat = Matrix.rotationX(2) mat:set(2, 2, 1.5) return mat");
                const auto matrix = get_userdata<mmm::Matrix>(L, -1);
                Assert::AreEqual(1.5f, matrix.get(2, 2));

                lua_close(L);
            }
        };
    }
}