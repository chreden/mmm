#include "AsteroidField.h"
#include "Type_AsteroidField.h"

namespace mmm
{
    AsteroidFieldPtr AsteroidField::create(types::Entity* entity)
    {
        return AsteroidFieldPtr(new AsteroidField(static_cast<types::AsteroidField*>(entity)));
    }

    AsteroidField::AsteroidField(types::AsteroidField* asteroid)
        : TerrainObject(asteroid)
    {
    }

    types::AsteroidField* AsteroidField::getAsteroidField() const
    {
        return static_cast<types::AsteroidField*>(getEntity());
    }
}
