#pragma once

#include "Ordnance.h"

namespace mmm
{
    namespace types { struct BeamToggle; }

    class BeamToggle : public Ordnance
    {
    public:
        static std::shared_ptr<BeamToggle> create(types::Entity* entity);
        Vector3 getStartPosition() const;
        Vector3 getEndPosition() const;
        void setStartPosition(const Vector3& position);
        void setEndPosition(const Vector3& position);
        int index(lua_State* L, const std::string& key) const override;
        int newindex(lua_State* L, const std::string& key) override;
    protected:
        explicit BeamToggle(types::BeamToggle* beamToggle);
    private:
        types::BeamToggle* getBeamToggle() const;
    };
}
