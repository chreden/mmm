#pragma once

struct lua_State;

namespace mmm
{
    class ST3D_Colour
    {
    public:
        ST3D_Colour() = default;
        ST3D_Colour(float r, float g, float b);
        explicit ST3D_Colour(unsigned int colour);
        ST3D_Colour operator+(const ST3D_Colour& right) const;
        ST3D_Colour operator-(const ST3D_Colour& right) const;
        ST3D_Colour operator*(float scale) const;
        ST3D_Colour operator/(float scale) const;
        static ST3D_Colour lerp(const ST3D_Colour& left, const ST3D_Colour& right, float amount);
        float r() const;
        float g() const;
        float b() const;
        void setR(float r);
        void setG(float g);
        void setB(float b);
    private:
        float r_ { 0.0f };
        float g_ { 0.0f };
        float b_ { 0.0f };
    };

    int colour_new(lua_State* L, const ST3D_Colour& colour);
    void colour_register(lua_State* L);
}

