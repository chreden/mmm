#include "AsteroidField.h"
#include "Type_AsteroidField.h"

namespace mmm
{
    AsteroidFieldPtr AsteroidField::create( types::Entity* entity )
    {
        return AsteroidFieldPtr( new AsteroidField( static_cast<types::AsteroidField*>( entity ) ) );
    }

    AsteroidField::AsteroidField( types::AsteroidField* asteroid )
        : TerrainObject( asteroid )
    {

    }

    float AsteroidField::getBoundingRadius() const
    {
        return getAsteroidField()->m_bounding_radius;
    }

    float AsteroidField::getAsteroidBeltTime() const
    {
        return getAsteroidField()->m_asteroid_belt_time;
    }

    void AsteroidField::setBoundingRadius(float value)
    {
        getAsteroidField()->m_bounding_radius = value;
    }

    void AsteroidField::setAsteroidBeltTime(float value)
    {
        getAsteroidField()->m_asteroid_belt_time = value;
    }

    types::AsteroidField* AsteroidField::getAsteroidField() const
    {
        return static_cast<types::AsteroidField*>( getEntity() );
    }

    void AsteroidField::allocateReplacement( luabind::detail::object_rep* object )
    {
        entity_allocate_replacement<AsteroidField>( object, boost::static_pointer_cast<AsteroidField>( shared_from_this() ) );
    }
}
