#include "Vector3.h"
#include "Matrix.h"
#include "LuaBinding.h"

namespace mmm
{
    namespace
    {
        int vector_add(lua_State* L);
        int vector_cross(lua_State* L);
        int vector_div(lua_State* L);
        int vector_dot(lua_State* L);
        int vector_lerp(lua_State* L);
        int vector_mul(lua_State* L);
        int vector_normalize(lua_State* L);
        int vector_sub(lua_State* L);

        int vector_metatable{ LUA_NOREF };
        const std::unordered_map<std::string, std::function<int(lua_State*, const Vector3&)>> getters
        {
            { "cross", [](auto&& L, auto&& V) noexcept { lua_pushcfunction(L, vector_cross); return 1; } },
            { "dot", [](auto&& L, auto&& V) noexcept { lua_pushcfunction(L, vector_dot); return 1; } },
            { "length", [](auto&& L, auto&& V) noexcept { lua_pushnumber(L, V.length()); return 1; } },
            { "lengthSquared", [](auto&& L, auto&& V) noexcept { lua_pushnumber(L, V.lengthSquared()); return 1; } },
            { "lerp", [](auto&& L, auto&& V) noexcept { lua_pushcfunction(L, vector_lerp); return 1; } },
            { "normalize", [](auto&& L, auto&& V) noexcept { lua_pushcfunction(L, vector_normalize); return 1; } },
            { "x", [](auto&& L, auto&& V) noexcept { lua_pushnumber(L, V.x); return 1; } },
            { "y", [](auto&& L, auto&& V) noexcept { lua_pushnumber(L, V.y); return 1; } },
            { "z", [](auto&& L, auto&& V) noexcept { lua_pushnumber(L, V.z); return 1; } },
        };

        int vector_add(lua_State* L)
        {
            const auto& self = get_userdata<Vector3>(L, 1);
            const auto& other = get_userdata<Vector3>(L, 2);
            return vector_new(L, self + other);
        }

        int vector_cross(lua_State* L)
        {
            const auto& self = get_userdata<Vector3>(L, 1);
            const auto& other = get_userdata<Vector3>(L, 2);
            return vector_new(L, self.cross(other));
        }

        int vector_div(lua_State* L)
        {
            const auto& self = get_userdata<Vector3>(L, 1);
            return vector_new(L, self / lua_tonumber(L, 2));
        }

        int vector_dot(lua_State* L)
        {
            const auto& self = get_userdata<Vector3>(L, 1);
            const auto& other = get_userdata<Vector3>(L, 2);
            lua_pushnumber(L, self.dot(other));
            return 1;
        }

        int vector_lerp(lua_State* L)
        {
            const auto& self = get_userdata<Vector3>(L, 1);
            const auto& other = get_userdata<Vector3>(L, 2);
            const float scalar = lua_tonumber(L, 3);
            return vector_new(L, self.lerp(other, scalar));
        }

        int vector_mul(lua_State* L)
        {
            const auto& self = get_userdata<Vector3>(L, 1);
            if (lua_type(L, 2) == LUA_TNUMBER)
            {
                return vector_new(L, self * lua_tonumber(L, 2));
            }

            const auto& other = get_userdata<Matrix>(L, 2);
            return vector_new(L, self * other);
        }

        int vector_normalize(lua_State* L)
        {
            const auto& self = get_userdata<Vector3>(L, 1);
            return vector_new(L, self.normalize());
        }

        int vector_sub(lua_State* L)
        {
            const auto& self = get_userdata<Vector3>(L, 1);
            const auto& other = get_userdata<Vector3>(L, 2);
            return vector_new(L, self - other);
        }

        int vector_index(lua_State* L)
        {
            auto& self = get_userdata<Vector3>(L, 1);
            const std::string key = lua_tostring(L, 2);
            const auto& getter = getters.find(key);
            if (getter != getters.end())
            {
                return getter->second(L, self);
            }
            return 0;
        }

        int vector_newindex(lua_State* L)
        {
            auto& self = get_userdata<Vector3>(L, 1);
            const std::string key = lua_tostring(L, 2);
            const float scalar = lua_tonumber(L, 3);

            if (key == "x")
            {
                self.x = scalar;
                return 0;
            }
            else if (key == "y")
            {
                self.y = scalar;
                return 0;
            }
            else if (key == "z")
            {
                self.z = scalar;
                return 0;
            }
            return 0;
        }

        int vector_constructor(lua_State* L)
        {
            if (lua_gettop(L) == 4)
            {
                return vector_new(L, Vector3(lua_tonumber(L, 2), lua_tonumber(L, 3), lua_tonumber(L, 4)));
            }
            return vector_new(L, Vector3());
        }
    }

    Vector3::Vector3(float nX, float nY, float nZ)
        : x(nX), y(nY), z(nZ)
    {
    }

    float Vector3::length() const noexcept
    {
        return sqrt(lengthSquared());
    }

    float Vector3::lengthSquared() const noexcept
    {
        return x * x + y * y + z * z;
    }

    Vector3 Vector3::normalize() const
    {
        float oneOverLen = 1.0 / length();
        return *this * oneOverLen;
    }

    float Vector3::dot(const Vector3& other) const
    {
        return x * other.x + y * other.y + z * other.z;
    }

    Vector3 Vector3::cross(const Vector3& other) const
    {
        return Vector3(y * other.y - z * other.y,
                       z * other.x - x * other.z,
                       x * other.y - y * other.x);
    }

    Vector3 Vector3::lerp(const Vector3& other, float scalar) const
    {
        if (scalar <= 0)
        {
            return *this;
        }
        else if(scalar >= 1)
        {
            return other;
        }
        return Vector3(x + (other.x - x) * scalar,
                       y + (other.y - y) * scalar,
                       z + (other.z - z) * scalar);
    }

    Vector3 Vector3::operator+(const Vector3& other) const
    {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    Vector3 Vector3::operator-(const Vector3& other) const
    {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    Vector3 Vector3::operator*(float other) const
    {
        return Vector3(x * other, y * other, z * other);
    }

    Vector3 Vector3::operator/(float other) const
    {
        return Vector3(x / other, y / other, z / other);
    }

    Vector3 Vector3::operator*(const Matrix& other) const
    {
        return other.transpose() * *this;
    }

    bool is_vector(lua_State* L, int index)
    {
        return equal_metatable(L, index, vector_metatable);
    }

    int vector_new(lua_State* L, const Vector3& value)
    {
        create_userdata(L, value);
        assign_metatable(L, vector_metatable);
        return 1;
    }

    void vector_register(lua_State* L)
    {
        lua_newtable(L);
        create_metatable(L, { { "__call", vector_constructor } });
        lua_setglobal(L, "Vector");

        vector_metatable = store_metatable(L,
            {
                { "__index", vector_index },
                { "__newindex", vector_newindex },
                { "__add", vector_add },
                { "__sub", vector_sub },
                { "__mul", vector_mul },
                { "__div", vector_div }
            });
    }
}
