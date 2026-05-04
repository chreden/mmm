#pragma once

namespace mmm
{
    class Objective
    {
    public:
        explicit Objective(int index);
        std::string getText() const;
        void setText(const std::string& value);
        bool getState() const;
        void setState(bool value);
    private:
        int index_;
    };

    int objective_new(lua_State* L, Objective objective);
    void objective_register(lua_State* L);
}
