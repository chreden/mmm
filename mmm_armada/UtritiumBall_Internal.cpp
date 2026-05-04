#include "UtritiumBall_Internal.h"
#include "UtritiumBallClass_Internal.h"
#include "Type_UtritiumBall.h"
#include "Type_UtritiumBallClass.h"

namespace mmm
{
    UtritiumBallPtr UtritiumBall::create(types::Entity* ent)
    {
        return UtritiumBallPtr(new UtritiumBall(static_cast<types::UtritiumBall*>(ent)));
    }

    UtritiumBall::UtritiumBall(types::UtritiumBall* type)
        : TerrainObject(type)
    {

    }

    std::shared_ptr<GameObjectClass> UtritiumBall::getClass() const
    {
        return std::shared_ptr<GameObjectClass>(new UtritiumBallClass(static_cast<types::UtritiumBallClass*>(getGameObject()->m_class)));
    }

    types::UtritiumBall* UtritiumBall::getUtritiumBall() const
    {
        return static_cast<types::UtritiumBall*>(getEntity());
    }

    float UtritiumBall::getTimeLeft() const
    {
        return getUtritiumBall()->m_time_left;
    }

    std::shared_ptr<Entity> UtritiumBall::getOwner() const
    {
        return createEntityPtr(GetEntity<types::Entity>(getUtritiumBall()->m_ownerHandle));
    }

    void UtritiumBall::setTimeLeft(float value)
    {
        getUtritiumBall()->m_time_left = value;
    }

    int UtritiumBall::index(lua_State* L, const std::string& key) const
    {
        if (key == "owner")
        {
            return entity_new(L, getOwner());
        }
        else if (key == "timeLeft")
        {
            lua_pushnumber(L, getTimeLeft());
            return 1;
        }
        return TerrainObject::index(L, key);
    }

    int UtritiumBall::newindex(lua_State* L, const std::string& key)
    {
        if (key == "timeLeft")
        {
            setTimeLeft(lua_tonumber(L, 3));
            return 0;
        }
        return TerrainObject::newindex(L, key);
    }
}
