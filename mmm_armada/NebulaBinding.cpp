#include "Nebula_Internal.h"

namespace mmm
{
    void nebula_register( lua_State* state )
    {
        using namespace luabind;
        module(state)
        [
            class_<Nebula, AreaEffectObject, EntityPtr>("Nebula")
                .property("allowConstruction", &Nebula::getCanBuildInNebula, &Nebula::setCanBuildInNebula)
                .property("deltaRoll", &Nebula::getDeltaRoll, &Nebula::setDeltaRoll)
                .property("deltaYaw", &Nebula::getDeltaYaw, &Nebula::setDeltaYaw)
                .property("deltaPitch", &Nebula::getDeltaPitch, &Nebula::setDeltaPitch)
        ];
    }
}
