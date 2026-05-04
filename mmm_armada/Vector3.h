#pragma once

struct lua_State;

namespace mmm
{
    struct Vector2
    {
        float x, y;
    };

    class Matrix;

    struct Vector3
    {
        explicit Vector3() = default;
        explicit Vector3(float nX, float nY, float nZ);

        float length() const;
        float lengthSquared() const;

        Vector3 normalize() const;
        float dot(const Vector3& other) const;
        Vector3 cross(const Vector3& other) const;
        Vector3 lerp(const Vector3& other, float scalar) const;

        Vector3 operator+(const Vector3& other) const;
        Vector3 operator-(const Vector3& other) const;
        Vector3 operator*(float other) const;
        Vector3 operator/(float other) const;
        Vector3 operator*(const Matrix& other) const;

        float x{ 0.0f };
        float y{ 0.0f };
        float z{ 0.0f };
    };

    bool is_vector(lua_State* L, int index);
    int vector_new(lua_State* L, const Vector3& value);
    void vector_register(lua_State* L);
}
