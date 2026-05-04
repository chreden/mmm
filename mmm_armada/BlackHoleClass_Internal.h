#pragma once

#include "AreaEffectObjectClass_Internal.h"

namespace mmm
{
    namespace types
    {
        struct BlackHoleClass;
    }

    class BlackHoleClass : public AreaEffectObjectClass
    {
    public:
        explicit BlackHoleClass(types::BlackHoleClass* type);
        float getGravityRadius() const;
        float getEventRadius() const;
        float getGravityForce() const;
        float getRotation() const;
        float getScaleSize() const;
        void setGravityRadius(float value);
        void setEventRadius(float value);
        void setGravityForce(float value);
        void setRotation(float value);
        void setScaleSize(float value);

        int index(lua_State* L, const std::string& key) const override;
        int newindex(lua_State* L, const std::string& key) override;
    private:
        types::BlackHoleClass* getBlackHoleClass() const;
    };
}
