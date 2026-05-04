#include "BeamToggle.h"
#include "Type_BeamToggle.h"
#include "LuaBinding.h"

namespace mmm
{
    std::shared_ptr<BeamToggle> BeamToggle::create(types::Entity* entity)
    {
        return std::shared_ptr<BeamToggle>(new BeamToggle(static_cast<types::BeamToggle*>(entity)));
    }

    BeamToggle::BeamToggle(types::BeamToggle* beamToggle)
        : Ordnance(beamToggle)
    {
    }

    types::BeamToggle* BeamToggle::getBeamToggle() const
    {
        return static_cast<types::BeamToggle*>(getEntity());
    }

    Vector3 BeamToggle::getStartPosition() const
    {
        return getBeamToggle()->startPos;
    }

    Vector3 BeamToggle::getEndPosition() const
    {
        return getBeamToggle()->endPos;
    }

    void BeamToggle::setStartPosition(const Vector3& position)
    {
        getBeamToggle()->startPos = position;
    }

    void BeamToggle::setEndPosition(const Vector3& position)
    {
        getBeamToggle()->endPos = position;
    }

    int BeamToggle::index(lua_State* L, const std::string& key) const
    {
        if (key == "endPosition")
        {
            return vector_new(L, getEndPosition());
        }
        else if (key == "startPosition")
        {
            return vector_new(L, getStartPosition());
        }
        return Ordnance::index(L, key);
    }

    int BeamToggle::newindex(lua_State* L, const std::string& key)
    {
        if (key == "endPosition")
        {
            setEndPosition(get_userdata<Vector3>(L, 3));
            return 0;
        }
        else if (key == "startPosition")
        {
            setStartPosition(get_userdata<Vector3>(L, 3));
            return 0;
        }
        return Ordnance::newindex(L, key);
    }
}
