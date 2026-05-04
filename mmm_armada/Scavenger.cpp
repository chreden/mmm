#include "Scavenger.h"
#include "Type_Scavenger.h"

namespace mmm
{
    ScavengerPtr Scavenger::create(types::Entity* scavenger)
    {
        return ScavengerPtr(new Scavenger(static_cast<types::Scavenger*>(scavenger)));
    }

    Scavenger::Scavenger(types::Scavenger* scavenger)
        : Craft(scavenger)
    {

    }
}