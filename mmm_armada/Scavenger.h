#pragma once

#include "Craft_Internal.h"

namespace mmm
{
    namespace types { struct Scavenger; }

    class Scavenger : public Craft
    {
    public:
        static std::shared_ptr<Scavenger> create(types::Entity* scavenger);
    protected:
    private:
        explicit Scavenger(types::Scavenger* scavenger);
    };
}
