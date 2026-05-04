#include "Mission_Internal.h"
#include "Game_Internal.h"
#include "LuaBinding.h"

namespace mmm
{
    namespace
    {
        Mission mission;

        int mission_finish(lua_State* L)
        {
            mission.end(lua_toboolean(L, 2), lua_tonumber(L, 3));
            return 0;
        }

        int mission_index(lua_State* L)
        {
            const std::string key = lua_tostring(L, 2);
            if (key == "finish")
            {
                lua_pushcfunction(L, mission_finish);
                return 1;
            }
            return 0;
        }
    }

    void Mission::end(bool success, float delay)
    {
        const float FinishingTime = Game().getTime() + delay;
        if(success)
        {
            getScriptInterface()->SucceedMission(FinishingTime, "");
        }
        else
        {
            getScriptInterface()->FailMission(FinishingTime, "");
        }
    }

    void mission_register(lua_State* L)
    {
        lua_newtable(L);
        create_metatable(L,
            {
                { "__index", mission_index }
            });
        lua_setglobal(L, "Mission");
    }
}