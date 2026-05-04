#pragma once

#include "Ordnance.h"

namespace mmm
{
    namespace types { struct Beam; }

    class Beam : public Ordnance
    {
    public:
        static std::shared_ptr<Beam> create(types::Entity* entity);
        virtual	~Beam(){};
        Vector3 getStartPos() const;
        Vector3 getEndPos() const;
        int index(lua_State* L, const std::string& key) const override;
    protected:
        explicit Beam(types::Beam* beam);
        types::Beam* getBeam() const;
    };
}
