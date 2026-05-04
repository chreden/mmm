#include "IonStorm_Internal.h"
#include "Type_IonStorm.h"
#include "LuaBinding.h"

namespace mmm
{
    IonStormPtr IonStorm::create(types::Entity* entity)
    {
        return IonStormPtr(new IonStorm(static_cast<types::IonStorm*>(entity)));
    }

    IonStorm::IonStorm(types::IonStorm* storm)
        : AreaEffectObject(storm)
    {

    }

    types::IonStorm::StormState IonStorm::getState() const
    {
        return getIonStorm()->m_stormState;
    }

    float IonStorm::getTimeLeft() const
    {
        return getIonStorm()->m_timeLeft;
    }

    float IonStorm::getCurrentScaleCount() const
    {
        return getIonStorm()->m_currentScaleCount;
    }

    void IonStorm::setState(types::IonStorm::StormState state)
    {
        getIonStorm()->m_stormState = state;
    }

    void IonStorm::setTimeLeft(float timeLeft)
    {
        getIonStorm()->m_timeLeft = timeLeft;
    }

    void IonStorm::setCurrentScaleCount(float count)
    {
        getIonStorm()->m_currentScaleCount = count;
    }

    types::IonStorm* IonStorm::getIonStorm() const
    {
        return static_cast<types::IonStorm*>(getEntity());
    }

    int IonStorm::index(lua_State* L, const std::string& key) const
    {
        if (key == "state")
        {
            lua_pushnumber(L, getState());
            return 1;
        }
        else if (key == "timeLeft")
        {
            lua_pushnumber(L, getTimeLeft());
            return 1;
        }
        return AreaEffectObject::index(L, key);
    }

    int IonStorm::newindex(lua_State* L, const std::string& key)
    {
        if (key == "timeLeft")
        {
            setTimeLeft(lua_tonumber(L, 3));
            return 0;
        }
        return AreaEffectObject::newindex(L, key);
    }

    void ionstorm_register(lua_State* L)
    {
        lua_newtable(L);
        create_enum(L, "State",
            {
                { "Closed", types::IonStorm::Closed },
                { "Closing", types::IonStorm::Closing },
                { "Open", types::IonStorm::Open },
                { "Opening", types::IonStorm::Opening }
            });
        lua_setglobal(L, "IonStorm");
    }
}
