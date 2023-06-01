#pragma once

#include "AreaEffectObject_Internal.h"

namespace mmm
{
    namespace types { struct Nebula; };

    class Nebula : public AreaEffectObject
    {
    public:
        static NebulaPtr create(types::Entity* entity);
        bool getCanBuildInNebula() const;
        void setCanBuildInNebula(bool value);
        float getDeltaRoll() const;
        float getDeltaPitch() const;
        float getDeltaYaw() const;
        void setDeltaRoll(float value);
        void setDeltaPitch(float value);
        void setDeltaYaw(float value);
        types::Nebula* getNebula() const;
    protected:
        virtual void allocateReplacement(luabind::detail::object_rep* object);
        explicit Nebula(types::Nebula* nebula);
    };

    void nebula_register(lua_State* state);
}
