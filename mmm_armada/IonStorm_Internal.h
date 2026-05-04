#pragma once

#include "AreaEffectObject_Internal.h"
#include "Type_IonStorm.h"

namespace mmm
{
    class IonStorm : public AreaEffectObject
    {
    public:
        static IonStormPtr create(types::Entity* entity);
        types::IonStorm::StormState getState() const;
        float getTimeLeft() const;
        float getCurrentScaleCount() const;
        void setState(types::IonStorm::StormState state);
        void setTimeLeft(float timeLeft);
        void setCurrentScaleCount(float count);
        types::IonStorm* getIonStorm() const;
        int index(lua_State* L, const std::string& key) const override;
        int newindex(lua_State* L, const std::string& key) override;
    protected:
        explicit IonStorm(types::IonStorm* storm);
    };

    void ionstorm_register(lua_State* L);
}
