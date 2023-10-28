#include "AsteroidField.h"

namespace mmm
{
    void asteroidfield_register( lua_State* state )
    {
        using namespace luabind;
        module(state)
        [
            class_<AsteroidField, TerrainObject, EntityPtr>( "AsteroidField" )
                // .property("boundingBox"
                .property("boundingRadius", &AsteroidField::getBoundingRadius, &AsteroidField::setBoundingRadius)
            // .property("rotationSpeed"
               .property("speed", &AsteroidField::getSpeed, &AsteroidField::setSpeed)
            // .property("repulsionDistance"
            // .property("maximumDistanceSqr"
            // .property("numberOfAsteroids"
            // .property("totalEnergy"
            // .property("asteroids"
            // .property("asteroidBeltLabel"
            // .property("closestOffset"
            // .property("closestTOnPath"
                .property("asteroidBeltTime", &AsteroidField::getAsteroidBeltTime, &AsteroidField::setAsteroidBeltTime)
                .property("asteroidBeltSpeedCoefficient", &AsteroidField::getAsteroidBeltSpeedCoefficient, &AsteroidField::setAsteroidBeltSpeedCoefficient)
            // .property("asteroidBelt"
        ];
    }
}
