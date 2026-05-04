#include "Beam_Internal.h"
#include "Type_Beam.h"

namespace mmm
{
    std::shared_ptr<Beam> Beam::create(types::Entity* entity)
    {
        return std::shared_ptr<Beam>(new Beam(static_cast<types::Beam*>(entity)));
    }

    Beam::Beam(types::Beam* beam)
        : Ordnance(beam)
    {
    }

    types::Beam* Beam::getBeam() const
    {
        return static_cast<types::Beam*>(getEntity());
    }

    Vector3 Beam::getStartPos() const
    {
        return getBeam()->m_startPos;
    }

    Vector3 Beam::getEndPos() const
    {
        return getBeam()->m_endPos;
    }

    int Beam::index(lua_State* L, const std::string& key) const
    {
        if (key == "endPosition")
        {
            return vector_new(L, getEndPos());
        }
        else if (key == "startPosition")
        {
            return vector_new(L, getStartPos());
        }
        return Ordnance::index(L, key);
    }
}
