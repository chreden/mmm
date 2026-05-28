#pragma once

#include "GameObject_Internal.h"

namespace mmm
{
    namespace types
    {
        struct TerrainObject;
    }

    class TerrainObject : public GameObject
    {
    public:
        static std::shared_ptr<TerrainObject> create(types::Entity* entity);
    protected:
        explicit TerrainObject(types::TerrainObject* object);
    };
}
