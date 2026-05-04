#pragma once

#include "Shipyard_Internal.h"

namespace mmm
{
    namespace types
    {
        struct Starbase;
    }

    class Starbase : public Shipyard
    {
    public:
        static StarbasePtr create(types::Entity* entity);
    protected:
        explicit Starbase(types::Starbase* starbase);
    private:
        types::Starbase* getStarbase() const;
    };
}
