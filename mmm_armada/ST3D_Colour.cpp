#include "ST3D_Colour.h"
#include "LuaBinding.h"
#include <format>

namespace mmm
{
    namespace
    {
        int color_metatable{ LUA_NOREF };

        int color_index(lua_State* L)
        {
            const auto& self = get_userdata<ST3D_Colour>(L, 1);
            const std::string key = lua_tostring(L, 2);

            if (key == "r")
            {
                lua_pushnumber(L, self.r());
                return 1;
            }
            else if (key == "g")
            {
                lua_pushnumber(L, self.g());
                return 1;
            }
            else if (key == "b")
            {
                lua_pushnumber(L, self.b());
                return 1;
            }
            return 0;
        }

        int color_newindex(lua_State* L)
        {
            auto& self = get_userdata<ST3D_Colour>(L, 1);
            const std::string key = lua_tostring(L, 2);

            if (key == "r")
            {
                self.setR(lua_tonumber(L, 3));
                return 0;
            }
            else if (key == "g")
            {
                self.setG(lua_tonumber(L, 3));
                return 0;
            }
            else if (key == "b")
            {
                self.setB(lua_tonumber(L, 3));
                return 0;
            }
            return 0;
        }

        int color_add(lua_State* L)
        {
            const auto& self = get_userdata<ST3D_Colour>(L, 1);
            const auto& other = get_userdata<ST3D_Colour>(L, 2);
            return colour_new(L, self + other);
        }

        int color_sub(lua_State* L)
        {
            const auto& self = get_userdata<ST3D_Colour>(L, 1);
            const auto& other = get_userdata<ST3D_Colour>(L, 2);
            return colour_new(L, self - other);
        }

        int color_mul(lua_State* L)
        {
            const auto& self = get_userdata<ST3D_Colour>(L, 1);
            return colour_new(L, self * lua_tonumber(L, 2));
        }

        int color_div(lua_State* L)
        {
            const auto& self = get_userdata<ST3D_Colour>(L, 1);
            return colour_new(L, self / lua_tonumber(L, 2));
        }

        int color_tostring(lua_State* L)
        {
            const auto& self = get_userdata<ST3D_Colour>(L, 1);
            lua_pushstring(L, std::format("{},{},{}", self.r(), self.g(), self.b()).c_str());
            return 1;
        }

        int color_lerp(lua_State* L)
        {
            return colour_new(L,
                ST3D_Colour::lerp(
                    get_userdata<ST3D_Colour>(L, 1),
                    get_userdata<ST3D_Colour>(L, 2),
                    lua_tonumber(L, 3)));
        }

        int color_class_index(lua_State* L)
        {
            const std::string key = lua_tostring(L, 2);
            if (key == "lerp")
            {
                lua_pushcfunction(L, color_lerp);
                return 1;
            }
            return 0;
        }

        int color_constructor(lua_State* L)
        {
            if (lua_gettop(L) == 1)
            {
                return colour_new(L, ST3D_Colour());
            }
            else if (lua_gettop(L) == 2)
            {
                return colour_new(L, ST3D_Colour(lua_tonumber(L, 2)));
            }
            else if (lua_gettop(L) == 4)
            {
                return colour_new(L, ST3D_Colour(lua_tonumber(L, 2), lua_tonumber(L, 3), lua_tonumber(L, 4)));
            }
            return 0;
        }
    }

    ST3D_Colour::ST3D_Colour(float r, float g, float b)
        : r_(r), g_(g), b_(b)
    {
    }

    ST3D_Colour::ST3D_Colour(unsigned int colour)
        : r_(((colour & 0xff0000) >> 16) / 255.0f),
          g_(((colour & 0x00ff00 ) >> 8) / 255.0f),
          b_(((colour & 0x0000ff )) / 255.0f)
    {
    }

    ST3D_Colour ST3D_Colour::operator+(const ST3D_Colour& right) const
    {
        return ST3D_Colour(r_ + right.r_, g_ + right.g_, b_ + right.b_);
    }

    ST3D_Colour ST3D_Colour::operator-(const ST3D_Colour& right) const
    {
        return ST3D_Colour(r_ - right.r_, g_ - right.g_, b_ - right.b_);
    }

    ST3D_Colour ST3D_Colour::operator*(float scale) const
    {
        return ST3D_Colour(r_ * scale, g_ * scale, b_ * scale);
    }

    ST3D_Colour ST3D_Colour::operator/(float scale) const
    {
        return ST3D_Colour(r_ / scale, g_ / scale, b_ / scale);
    }

    ST3D_Colour ST3D_Colour::lerp(const ST3D_Colour& left, const ST3D_Colour& right, float amount)
    {
        return ST3D_Colour(left.r_ + (right.r_ - left.r_) * amount,
                           left.g_ + (right.g_ - left.g_) * amount,
                           left.b_ + (right.b_ - left.b_) * amount);
    }

    float ST3D_Colour::r() const
    {
        return r_;
    }

    float ST3D_Colour::g() const
    {
        return g_;
    }

    float ST3D_Colour::b() const
    {
        return b_;
    }

    void ST3D_Colour::setR(float r)
    {
        r_ = r;
    }

    void ST3D_Colour::setG(float g)
    {
        g_ = g;
    }

    void ST3D_Colour::setB(float b)
    {
        b_ = b;
    }

    int colour_new(lua_State* L, const ST3D_Colour& colour)
    {
        create_userdata(L, colour);
        assign_metatable(L, color_metatable);
        return 1;
    }

    void colour_register(lua_State* L)
    {
        lua_newtable(L);
        create_metatable(L,
            {
                { "__index", color_class_index },
                { "__call", color_constructor }
            });
        lua_setglobal(L, "Color");

        color_metatable = store_metatable(L,
            {
                { "__index", color_index },
                { "__newindex", color_newindex },
                { "__add", color_add },
                { "__sub", color_sub },
                { "__mul", color_mul },
                { "__div", color_div },
                { "__tostring", color_tostring }
            });
    }
}
