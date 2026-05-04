#pragma once

#include "TerrainObjectClass_Internal.h"

namespace mmm
{
    namespace types
    {
        struct LatinumNebulaClass;
    }

    class LatinumNebulaClass : public TerrainObjectClass
    {
    public:
        explicit LatinumNebulaClass(types::LatinumNebulaClass* nebula);
        float getRotationSpeed() const;
        void  setRotationSpeed(float value);
        int index(lua_State* L, const std::string& key) const override;
        int newindex(lua_State* L, const std::string& key) override;
    private:
        types::LatinumNebulaClass* getLatinumNebula() const;
    };
}
