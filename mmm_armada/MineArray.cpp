#include "MineArray.h"
#include "MineArrayType.h"
#include "LuaBinding.h"

namespace mmm
{
    std::shared_ptr<MineArray> MineArray::create(types::Entity* mine)
    {
        return std::shared_ptr<MineArray>(new MineArray(static_cast<types::MineArray*>(mine)));
    }

    MineArray::MineArray(types::MineArray* mine)
        : Craft(mine)
    {

    }

    types::MineArray* MineArray::getMineArray() const
    {
        return static_cast<types::MineArray*>(getEntity());
    }

    Vector3 MineArray::getHome() const
    {
        return getMineArray()->m_home;
    }

    std::shared_ptr<Entity> MineArray::getTarget() const
    {
        return createEntityPtr(GetEntity<types::Entity>(getMineArray()->m_target));
    }

    eMineArrayState MineArray::getState() const
    {
        return getMineArray()->m_state;
    }

    void MineArray::setHome(const Vector3& value)
    {
        getMineArray()->m_home = value;
    }

    int MineArray::index(lua_State* L, const std::string& key) const
    {
        if (key == "home")
        {
            return vector_new(L, getHome());
        }
        else if (key == "state")
        {
            lua_pushnumber(L, getState());
            return 1;
        }
        else if (key == "target")
        {
            return entity_new(L, getTarget());
        }
        return Craft::index(L, key);
    }

    int MineArray::newindex(lua_State* L, const std::string& key)
    {
        if (key == "home")
        {
            setHome(get_userdata<Vector3>(L, 3));
        }
        return Craft::newindex(L, key);
    }

    void minearray_register(lua_State* L)
    {
        lua_newtable(L);
        create_enum(L, "State",
            {
                { "DoNothing", MINE_ARRAY_DO_NOTHING },
                { "FindTarget", MINE_ARRAY_FIND_TARGET },
                { "FindHome", MINE_ARRAY_FIND_HOME }
            });
        lua_setglobal(L, "MineArray");
    }
}
