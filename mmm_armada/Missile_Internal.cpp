#include "Missile_Internal.h"
#include "Type_Missile.h"
#include "LuaBinding.h"

namespace mmm
{
    MissilePtr Missile::create(types::Entity* entity)
    {
        return MissilePtr(new Missile(static_cast<types::Missile*>(entity)));
    }

    Missile::Missile(types::Missile* missile)
        : Ordnance(missile)
    {

    }

    types::Missile* Missile::getMissile() const
    {
        return static_cast<types::Missile*>(getEntity());
    }

    Vector3 Missile::getOmega() const
    {
        return getMissile()->omega;
    }

    float Missile::getSeekTimer() const
    {
        return getMissile()->seekTimer;
    }

    float Missile::getTurnLim2() const
    {
        return getMissile()->turnLim2;
    }

    void Missile::setOmega(const Vector3& value)
    {
        getMissile()->omega = value;
    }

    void Missile::setTurnLim2(float value)
    {
        getMissile()->turnLim2 = value;
    }

    int Missile::index(lua_State* L, const std::string& key) const
    {
        if (key == "omega")
        {
            return vector_new(L, getOmega());
        }
        else if (key == "seekTimer")
        {
            lua_pushnumber(L, getSeekTimer());
            return 1;
        }
        else if (key == "turnLim2")
        {
            lua_pushnumber(L, getTurnLim2());
            return 1;
        }
        return Ordnance::index(L, key);
    }

    int Missile::newindex(lua_State* L, const std::string& key)
    {
        if (key == "omega")
        {
            setOmega(get_userdata<Vector3>(L, 3));
            return 0;
        }
        else if (key == "turnLim2")
        {
            setTurnLim2(lua_tonumber(L, 3));
            return 0;
        }
        return Ordnance::newindex(L, key);
    }
}
