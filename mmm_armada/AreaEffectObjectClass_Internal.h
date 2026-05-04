#pragma once

#include "TerrainObjectClass_Internal.h"

namespace mmm
{
    namespace types
    {
        struct AreaEffectObjectClass;
    }

    class AreaEffectObjectClass : public TerrainObjectClass
    {
    public:
        explicit AreaEffectObjectClass(types::AreaEffectObjectClass* type);

        float getRadius() const;
        void  setRadius(float value);

        int index(lua_State* L, const std::string& key) const override;
        int newindex(lua_State* L, const std::string& key) override;
    private:
        types::AreaEffectObjectClass* getAreaEffectObjectClass() const;
    };
}
