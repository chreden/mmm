#include "Matrix.h"
#include "LuaBinding.h"

namespace mmm
{
    namespace
    {
        int matrix_metatable{ LUA_NOREF };

        int matrix_transpose(lua_State* L)
        {
            const auto& self = get_userdata<Matrix>(L, 1);
            return matrix_new(L, self.transpose());
        }

        int matrix_get(lua_State* L)
        {
            const auto& self = get_userdata<Matrix>(L, 1);
            lua_pushnumber(L, self.get(lua_tonumber(L, 2), lua_tonumber(L, 3)));
            return 1;
        }

        int matrix_set(lua_State* L)
        {
            auto& self = get_userdata<Matrix>(L, 1);
            self.set(lua_tonumber(L, 2), lua_tonumber(L, 3), lua_tonumber(L, 4));
            return 0;
        }

        int matrix_index(lua_State* L)
        {
            const std::string key = lua_tostring(L, 2);
            if (key == "get")
            {
                lua_pushcfunction(L, matrix_get);
                return 1;
            }
            else if (key == "set")
            {
                lua_pushcfunction(L, matrix_set);
                return 1;
            }
            else if (key == "transpose")
            {
                lua_pushcfunction(L, matrix_transpose);
                return 1;
            }
            return 0;
        }

        int matrix_mul(lua_State* L)
        {
            const auto& self = get_userdata<Matrix>(L, 1);
            if (is_matrix(L, 2))
            {
                return matrix_new(L, self * get_userdata<Matrix>(L, 2));
            }
            else if (is_vector(L, 2))
            {
                return vector_new(L, self * get_userdata<Vector3>(L, 2));
            }
            return 0;
        }

        int matrix_rotation(lua_State* L)
        {
            if (lua_type(L, 2) == LUA_TNUMBER && lua_gettop(L) == 4)
            {
                return matrix_new(L, Matrix::rotation(lua_tonumber(L, 2), lua_tonumber(L, 3), lua_tonumber(L, 4)));
            }
            else if (is_vector(L, 2))
            {
                return matrix_new(L, Matrix::rotation(get_userdata<Vector3>(L, 2)));
            }
            return 0;
        }

        int matrix_rotation_x(lua_State* L)
        {
            return matrix_new(L, Matrix::rotationX(lua_tonumber(L, 2)));
        }

        int matrix_rotation_y(lua_State* L)
        {
            return matrix_new(L, Matrix::rotationY(lua_tonumber(L, 2)));
        }

        int matrix_rotation_z(lua_State* L)
        {
            return matrix_new(L, Matrix::rotationZ(lua_tonumber(L, 2)));
        }

        int matrix_scaling(lua_State* L)
        {
            if (lua_type(L, 2) == LUA_TNUMBER)
            {
                if (lua_gettop(L) == 4)
                {
                    return matrix_new(L, Matrix::scaling(lua_tonumber(L, 2), lua_tonumber(L, 3), lua_tonumber(L, 4)));
                }
                return matrix_new(L, Matrix::scaling(lua_tonumber(L, 2)));
            }
            else if (is_vector(L, 2))
            {
                return matrix_new(L, Matrix::scaling(get_userdata<Vector3>(L, 2)));
            }
            return 0;
        }

        int matrix_translation(lua_State* L)
        {
            if (lua_type(L, 2) == LUA_TNUMBER && lua_gettop(L) == 4)
            {
                return matrix_new(L, Matrix::translation(lua_tonumber(L, 2), lua_tonumber(L, 3), lua_tonumber(L, 4)));
            }
            else if (is_vector(L, 2))
            {
                return matrix_new(L, Matrix::translation(get_userdata<Vector3>(L, 2)));
            }
            return 0;
        }

        int matrix_class_index(lua_State* L)
        {
            const std::string key = lua_tostring(L, 2);

            if (key == "rotation")
            {
                lua_pushcfunction(L, matrix_rotation);
                return 1;
            }
            else if (key == "rotationX")
            {
                lua_pushcfunction(L, matrix_rotation_x);
                return 1;
            }
            else if (key == "rotationY")
            {
                lua_pushcfunction(L, matrix_rotation_y);
                return 1;
            }
            else if (key == "rotationZ")
            {
                lua_pushcfunction(L, matrix_rotation_z);
                return 1;
            }
            else if (key == "scaling")
            {
                lua_pushcfunction(L, matrix_scaling);
                return 1;
            }
            else if (key == "translation")
            {
                lua_pushcfunction(L, matrix_translation);
                return 1;
            }
            return 0;
        }

        bool is_matrix(lua_State* L, int index)
        {
            return equal_metatable(L, index, matrix_metatable);
        }

        int matrix_constructor(lua_State* L)
        {
            return matrix_new(L, Matrix());
        }
    }

    Matrix::Matrix()
    {
        //Default constructor sets the matrix to be identity.
        memset(m_, 0, sizeof(m_)); //Set identity fields.
        m_[0][0] = 1;
        m_[1][1] = 1;
        m_[2][2] = 1;
        m_[3][3] = 1;
    }

    Matrix::Matrix(const Matrix& other)
    {
        memcpy(m_, other.m_, sizeof(m_));
    }

    Matrix& Matrix::operator=(const Matrix& other)
    {
        memcpy(m_, other.m_, sizeof(m_));
        return *this;
    }

    Matrix Matrix::operator*(const Matrix& other) const
    {
        Matrix newMatrix;
        memset(newMatrix.m_, 0, sizeof(newMatrix.m_));

        for(int i = 0; i < 4; ++i)
        {
            for(int j = 0; j < 4; ++j)
            {
                for(int k = 0; k < 4; ++k)
                {
                    newMatrix.m_[i][j] += m_[i][k] * other.m_[k][j];
                }
            }
        }

        return newMatrix;
    }

    Vector3 Matrix::operator*(const Vector3& other) const
    {
        float nv[4] = { 0, 0, 0, 0 };
        float v[4] = { other.x, other.y, other.z, 1 };

        //We have 4 rows in the matrix, so 4 in the outer loop (i guess
        //we are doing rows first?)
        for(int i = 0; i < 4; ++i)
        {
            for(int j = 0; j < 4; ++j)
            {
                nv[i] += m_[j][i] * v[j];
            }
        }
        return Vector3(nv[0] / nv[3], nv[1] / nv[3], nv[2] / nv[3]);
    }

    Matrix Matrix::transpose() const
    {
        Matrix newMatrix;
        for(int i = 0; i < 4; ++i)
        {
            for(int j = 0; j < 4; ++j)
            {
                newMatrix.m_[i][j] = m_[j][i];
            }
        }
        return newMatrix;
    }

    float Matrix::get(int row, int column) const
    {
        if(row > 0 && row <= 4 && 
            column > 0 && column <= 4)
        {
            return m_[row - 1][column - 1];
        }
        return 0;
    }

    void Matrix::set(int row, int column, float value)
    {
        if(row > 0 && row <= 4 && 
            column > 0 && column <= 4)
        {
            m_[row - 1][column - 1] = value;
        }
    }

    Matrix Matrix::rotationY(float angle)
    {
        Matrix newMatrix;

        float cosAng = cos(angle);
        float sinAng = sin(angle);

        newMatrix.m_[0][0] = cosAng;
        newMatrix.m_[0][2] = -sinAng;
        newMatrix.m_[2][0] = sinAng;
        newMatrix.m_[2][2] = cosAng;

        return newMatrix;
    }

    Matrix Matrix::rotationX(float angle)
    {
        Matrix newMatrix;

        float cosAng = cos(angle);
        float sinAng = sin(angle);

        newMatrix.m_[1][1] = cosAng;
        newMatrix.m_[1][2] = sinAng;
        newMatrix.m_[2][1] = -sinAng;
        newMatrix.m_[2][2] = cosAng;

        return newMatrix;
    }

    Matrix Matrix::rotationZ(float angle)
    {
        Matrix newMatrix;

        float cosAng = cos(angle);
        float sinAng = sin(angle);

        newMatrix.m_[0][0] = cosAng;
        newMatrix.m_[0][1] = sinAng;
        newMatrix.m_[1][0] = -sinAng;
        newMatrix.m_[1][1] = cosAng;

        return newMatrix;
    }

    Matrix Matrix::rotation(float x, float y, float z)
    {
        return rotationX(x) * rotationY(y) * rotationZ(z);
    }

    Matrix Matrix::rotation(const Vector3& xyz)
    {
        return rotation(xyz.x, xyz.y, xyz.z);
    }

    Matrix Matrix::translation(const Vector3& trans)
    {
        return translation(trans.x, trans.y, trans.z);
    }

    Matrix Matrix::translation(float x, float y, float z)
    {
        Matrix newMatrix;

        newMatrix.m_[3][0] = x;
        newMatrix.m_[3][1] = y;
        newMatrix.m_[3][2] = z;

        return newMatrix;
    }

    Matrix Matrix::scaling(float amount)
    {
        return scaling(amount, amount, amount);
    }

    Matrix Matrix::scaling(float x, float y, float z)
    {
        Matrix newMatrix;

        newMatrix.m_[0][0] = x;
        newMatrix.m_[1][1] = y;
        newMatrix.m_[2][2] = z;

        return newMatrix;
    }

    Matrix Matrix::scaling(const Vector3& amount)
    {
        return scaling(amount.x, amount.y, amount.z);
    }

    bool is_matrix(lua_State* L, int index)
    {
        return equal_metatable(L, index, matrix_metatable);
    }

    int matrix_new(lua_State* L, const Matrix& matrix)
    {
        create_userdata(L, matrix);
        assign_metatable(L, matrix_metatable);
        return 1;
    }

    void matrix_register(lua_State* L)
    {
        lua_newtable(L);
        create_metatable(L,
            {
                { "__index", matrix_class_index },
                { "__call", matrix_constructor }
            });
        lua_setglobal(L, "Matrix");

        matrix_metatable = store_metatable(L,
            {
                { "__index", matrix_index },
                { "__mul", matrix_mul }
            });
    }
}

