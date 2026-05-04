#pragma once

#include "BackgroundObjectClass_Internal.h"

namespace mmm
{
    namespace types
    {	
        struct BackgroundPlanetClass;
    }

    class BackgroundPlanetClass : public BackgroundObjectClass
    {
    public:
        explicit BackgroundPlanetClass(types::BackgroundPlanetClass* planet);
        float getRotationRate() const;
        float getCrewModifier() const;
        void setRotationRate(float value);
        void setCrewModifier(float value);
        int index(lua_State* L, const std::string& key) const override;
        int newindex(lua_State* L, const std::string& key) override;
    private:
        types::BackgroundPlanetClass* getBackgroundPlanetClass() const;
    };
}
