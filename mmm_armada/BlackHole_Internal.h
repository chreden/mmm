#pragma once

#include "AreaEffectObject_Internal.h"

namespace mmm
{
    namespace types { struct BlackHole; }

    class BlackHole : public AreaEffectObject
    {
    public:
        static BlackHolePtr   create(types::Entity* entity);
        virtual std::shared_ptr<GameObjectClass> getClass() const;
    protected:
        explicit   BlackHole(types::BlackHole* type);
    };
}
