#include "Nebula_Internal.h"
#include "Type_Nebula.h"

namespace mmm
{
    NebulaPtr Nebula::create(types::Entity* entity)
    {
        return NebulaPtr(new Nebula(static_cast<types::Nebula*>( entity )));
    }

    Nebula::Nebula(types::Nebula* nebula)
        : AreaEffectObject(nebula)
    {
    }

    bool Nebula::getCanBuildInNebula() const
    {
        return getNebula()->m_canWeBuildInHere;
    }

    void Nebula::setCanBuildInNebula(bool value)
    {
        getNebula()->m_canWeBuildInHere = value;
    }

    float Nebula::getDeltaRoll() const
    {
        return getNebula()->delta_roll;
    }

    float Nebula::getDeltaPitch() const
    {
        return getNebula()->delta_pitch;
    }

    float Nebula::getDeltaYaw() const
    {
        return getNebula()->delta_yaw;
    }

    void Nebula::setDeltaRoll(float value)
    {
        getNebula()->delta_roll = value;
    }

    void Nebula::setDeltaPitch(float value)
    {
        getNebula()->delta_pitch = value;
    }

    void Nebula::setDeltaYaw(float value)
    {
        getNebula()->delta_yaw = value;
    }

    types::Nebula* Nebula::getNebula() const
    {
        return static_cast<types::Nebula*>(getEntity());
    }

    void Nebula::allocateReplacement(luabind::detail::object_rep* obj)
    {
        entity_allocate_replacement<Nebula>(obj, boost::static_pointer_cast<Nebula>(shared_from_this()));
    }
}
