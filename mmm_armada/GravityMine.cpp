#include "GravityMine.h"
#include "GravityMineType.h"

namespace mmm
{
    std::shared_ptr<GravityMine> GravityMine::create(types::Entity* entity)
    {
        return std::shared_ptr<GravityMine>(new GravityMine(static_cast<types::GravityMine*>(entity)));
    }

    GravityMine::GravityMine(types::GravityMine* gravityMine)
        : Mine(gravityMine)
    {

    }

    types::GravityMine* GravityMine::getGravityMine() const
    {
        return static_cast<types::GravityMine*>(getEntity());
    }
}