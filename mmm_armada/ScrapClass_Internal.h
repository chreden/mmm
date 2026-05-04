#pragma once

#include "TerrainObjectClass_Internal.h"

namespace mmm
{
    namespace types
    {
        struct ScrapClass;
    }

    class ScrapClass : public TerrainObjectClass
    {
    public:
        explicit ScrapClass(types::ScrapClass* obj);
        float getRotationSpeed() const;
        void setRotationSpeed(float value);
        int index(lua_State* L, const std::string& key) const override;
        int newindex(lua_State* L, const std::string& key) override;
    private:
        types::ScrapClass* getScrapClass() const;
    };
}
