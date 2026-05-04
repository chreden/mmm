#pragma once

#include "TerrainObject_Internal.h"

namespace mmm
{
    namespace types
    {
        struct LatinumNebula;
    }

    class LatinumNebula
        : public TerrainObject
    {
    public:
        static LatinumNebulaPtr create(types::Entity* entity);
        virtual std::shared_ptr<GameObjectClass> getClass() const;
    protected:
        explicit	 LatinumNebula(types::LatinumNebula* nebula);
    };
}
