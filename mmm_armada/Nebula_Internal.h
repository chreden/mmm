#pragma once

#include "AreaEffectObject_Internal.h"

namespace mmm
{
    namespace types { struct Nebula; };

    class Nebula : public AreaEffectObject
    {
    public:
        static std::shared_ptr<Nebula> create(types::Entity* entity);
        bool getCanBuildInNebula() const;
        void setCanBuildInNebula(bool value);
        float getDeltaRoll() const;
        float getDeltaPitch() const;
        float getDeltaYaw() const;
        void setDeltaRoll(float value);
        void setDeltaPitch(float value);
        void setDeltaYaw(float value);
        types::Nebula* getNebula() const;
        int index(lua_State* L, const std::string& key) const override;
        int newindex(lua_State* L, const std::string& key) override;
    protected:
        explicit Nebula(types::Nebula* nebula);
    };
}
