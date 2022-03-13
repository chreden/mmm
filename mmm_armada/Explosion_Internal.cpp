#include "Explosion_Internal.h"
#include "Type_Explosion.h"

namespace mmm
{
	Explosion::Explosion( types::Explosion* explosion )
		: Entity( explosion )
	{

	}

	types::Explosion*
	Explosion::getExplosion( ) const
	{
		return static_cast<types::Explosion*>( getEntity() );
	}

	EntityPtr
	Explosion::getEntityResponsible( ) const
	{
		return createEntityPtr( GetEntity<types::Entity>( getExplosion()->m_whoIsResponsibleForBlast ) );
	}

	float
	Explosion::getRadius( ) const
	{
		return getExplosion()->m_radius;
	}

	bool
	Explosion::getSoundPlayed() const
	{
		return getExplosion()->m_soundPlayed;
	}
}
