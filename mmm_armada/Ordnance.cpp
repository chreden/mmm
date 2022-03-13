#include "Ordnance.h"
#include "Team_Internal.h"
#include "OrdnanceType.h"
#include "OrdnanceDamage.h"

namespace mmm
{
	Ordnance::Ordnance( types::Ordnance* ordnance )
		: Entity( ordnance )
	{

	}

	types::Ordnance*
	Ordnance::getOrdnance( ) const
	{
		return static_cast<types::Ordnance*>( getEntity() );
	}

	TeamPtr
	Ordnance::getTeam( ) const
	{
		return TeamPtr( new Team( getOrdnance()->m_team_number ) );
	}

	Vector3
	Ordnance::getTargetLocation( ) const
	{
		return getOrdnance()->targetLocationPos;
	}

	bool
	Ordnance::getReflected( ) const
	{
		return getOrdnance()->m_reflected;
	}

	EntityPtr
	Ordnance::getOwner() const
	{
		return createEntityPtr( GetEntity<types::Entity>( getOrdnance()->ownerHandle ) );
	}

	EntityPtr
	Ordnance::getTarget() const
	{
		return createEntityPtr( GetEntity<types::Entity>( getOrdnance()->targetHandle ) );
	}

	float
	Ordnance::getLifetime() const
	{
		return getOrdnance()->m_lifetime;
	}

	Vector3
	Ordnance::getVelocity() const
	{
		return getOrdnance()->m_euler.m_vel;
	}

	OrdnanceDamagePtr 
	Ordnance::getDamage() const
	{
		return OrdnanceDamage::create( getOrdnance() );
	}

	void
	Ordnance::setTarget( EntityPtr target )
	{
		if( target )
		{
			getOrdnance()->targetHandle = target->getID();	
		}
		else
		{
			getOrdnance()->targetHandle = 0;
		}
	}

	void		
	Ordnance::setLifetime( float value )
	{
		getOrdnance()->m_lifetime = value;
	}

	void
	Ordnance::setVelocity( const Vector3& value )
	{
		getOrdnance()->m_euler.m_vel = value;
	}

	void
	Ordnance::allocateReplacement( luabind::detail::object_rep* obj )
	{
		entity_allocate_replacement<Ordnance>( obj, boost::static_pointer_cast<Ordnance>( shared_from_this() ) );
	}
}
