#pragma once

#include "TerrainObject_Internal.h"

namespace mmm
{
    namespace types { struct Scrap; }

    class Scrap : public TerrainObject
    {
    public:
        static std::shared_ptr<Scrap> create( types::Entity* entity );
        virtual std::shared_ptr<GameObjectClass> getClass() const;
    protected:
        explicit Scrap(types::Scrap* scrap);
    };
}
