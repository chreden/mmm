#pragma once

#include "TerrainObject_Internal.h"

namespace mmm
{
    namespace types
    {
        struct AreaEffectObject;
    }

    class AreaEffectObject  : public TerrainObject
    {
    public:
        static AreaEffectObjectPtr create(types::Entity* entity);
        virtual std::shared_ptr<GameObjectClass> getClass() const;
    protected:
        explicit AreaEffectObject(types::AreaEffectObject* object);
    };
}
