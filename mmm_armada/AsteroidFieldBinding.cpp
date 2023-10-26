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
            // .property("speed"
            // .property("repulsionDistance"
            // .property("maximumDistanceSqr"
            // .property("numberOfAsteroids"
            // .property("totalEnergy"
            // .property("asteroids"
            // .property("asteroidBeltLabel"
            // .property("closestOffset"
            // .property("closestTOnPath"
                .property("asteroidBeltTime", &AsteroidField::getAsteroidBeltTime, &AsteroidField::setAsteroidBeltTIme)
            // .property("asteroidBeltSpeedCoefficient"
            // .property("asteroidBelt"
        ];
    }
}
