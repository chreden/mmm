#include "BackgroundPlanetClass_Internal.h"
#include "Type_BackgroundPlanetClass.h"

namespace mmm
{
    BackgroundPlanetClass::BackgroundPlanetClass(types::BackgroundPlanetClass* planet)
        : BackgroundObjectClass(planet)
    {
    }

    types::BackgroundPlanetClass* BackgroundPlanetClass::getBackgroundPlanetClass() const
    {
        return static_cast<types::BackgroundPlanetClass*>(getClass());
    }

    float BackgroundPlanetClass::getRotationRate() const
    {
        return getBackgroundPlanetClass()->rotationRate;
    }

    float BackgroundPlanetClass::getCrewModifier() const
    {
        return getBackgroundPlanetClass()->crewModifier;
    }

    void BackgroundPlanetClass::setRotationRate(float value)
    {
        getBackgroundPlanetClass()->rotationRate = value;
    }

    void BackgroundPlanetClass::setCrewModifier(float value)
    {
        getBackgroundPlanetClass()->crewModifier = value;
    }

    int BackgroundPlanetClass::index(lua_State* L, const std::string& key) const
    {
        if (key == "crewModifier")
        {
            lua_pushnumber(L, getCrewModifier());
            return 1;
        }
        else if (key == "rotationRate")
        {
            lua_pushnumber(L, getRotationRate());
            return 1;
        }
        return BackgroundObjectClass::index(L, key);
    }

    int BackgroundPlanetClass::newindex(lua_State* L, const std::string& key)
    {
        if (key == "crewModifier")
        {
            setCrewModifier(lua_tonumber(L, 3));
            return 0;
        }
        else if (key == "rotationRate")
        {
            setRotationRate(lua_tonumber(L, 3));
            return 0;
        }
        return BackgroundObjectClass::newindex(L, key);
    }
}
