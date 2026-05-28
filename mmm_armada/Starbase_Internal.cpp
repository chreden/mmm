#include "Starbase_Internal.h"
#include "Type_Starbase.h"

namespace mmm
{
    std::shared_ptr<Starbase> Starbase::create(types::Entity* entity)
    {
        return std::shared_ptr<Starbase>(new Starbase(static_cast<types::Starbase*>(entity)));
    }

    Starbase::Starbase(types::Starbase* starbase)
        : Shipyard(starbase)
    {
    }

    types::Starbase* Starbase::getStarbase() const
    {
        return static_cast<types::Starbase*>(getEntity());
    }
}
