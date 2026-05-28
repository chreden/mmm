#include "Scavenger.h"
#include "Type_Scavenger.h"

namespace mmm
{
    std::shared_ptr<Scavenger> Scavenger::create(types::Entity* scavenger)
    {
        return std::shared_ptr<Scavenger>(new Scavenger(static_cast<types::Scavenger*>(scavenger)));
    }

    Scavenger::Scavenger(types::Scavenger* scavenger)
        : Craft(scavenger)
    {

    }
}