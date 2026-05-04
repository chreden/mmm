#include "Objective.h"
#include "Objectives_Internal.h"
#include "LuaBinding.h"

namespace mmm
{
    namespace
    {
        int objective_index(lua_State* L)
        {
            const auto& self = get_userdata<Objective>(L, 1);
            const std::string key = lua_tostring(L, 2);

            if (key == "state")
            {
                lua_pushboolean(L, self.getState());
                return 1;
            }
            else if (key == "text")
            {
                lua_pushstring(L, self.getText().c_str());
                return 1;
            }
            return 0;
        }

        int objective_newindex(lua_State* L)
        {
            auto& self = get_userdata<Objective>(L, 1);
            const std::string key = lua_tostring(L, 2);

            if (key == "state")
            {
                self.setState(lua_toboolean(L, 3));
                return 0;
            }
            else if (key == "text")
            {
                self.setText(lua_tostring(L, 3));
                return 0;
            }
            return 0;
        }
    }

    Objective::Objective(int index)
        : index_(index)
    {
    }

    std::string Objective::getText() const
    {
        return Objectives().getObjective(index_);
    }

    bool Objective::getState() const
    {
        return Objectives().getObjectiveState(index_);
    }

    void Objective::setState(bool value)
    {
        return Objectives().setObjectiveState(index_, value);
    }

    void Objective::setText(const std::string& value)
    {
        return Objectives().setObjective(index_, value);
    }

    int objective_new(lua_State* L, Objective objective)
    {
        create_userdata(L, objective);
        create_metatable(L,
            {
                { "__index", objective_index },
                { "__newindex", objective_newindex },
            });
        return 1;
    }
}
