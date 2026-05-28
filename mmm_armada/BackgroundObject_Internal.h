#pragma once

#include "TerrainObject_Internal.h"

namespace mmm
{
    namespace types
    {
        struct BackgroundObject;
    }

    class BackgroundObject : public TerrainObject
    {
    public:
        static std::shared_ptr<BackgroundObject> create(types::Entity* entity);
        std::shared_ptr<GameObjectClass> getClass() const override;
    protected:
        explicit BackgroundObject(types::BackgroundObject* object);
    };
}
