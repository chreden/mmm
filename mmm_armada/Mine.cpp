#include "Mine.h"
#include "MineType.h"
#include "LuaBinding.h"

namespace mmm
{
    MinePtr Mine::create(types::Entity* entity)
    {
        return MinePtr(new Mine(static_cast<types::Mine*>(entity)));
    }

    Mine::Mine(types::Mine* mine)
        : Ordnance(mine)
    {

    }

    types::Mine* Mine::getMine() const
    {
        return static_cast<types::Mine*>(getEntity());
    }

    eMineStatus Mine::getMineStatus() const
    {
        return getMine()->m_mineStatus;
    }

    int Mine::index(lua_State* L, const std::string& key) const
    {
        if (key == "state")
        {
            lua_pushnumber(L, getMineStatus());
            return 1;
        }
        return Ordnance::index(L, key);
    }

    void mine_register(lua_State* L)
    {
        lua_newtable(L);
        create_enum(L, "State",
            {
                { "Deploy", StateDeploy },
                { "Detect", StateDetect },
                { "Chase", StateChase },
            });
        lua_setglobal(L, "Mine");
    }
}