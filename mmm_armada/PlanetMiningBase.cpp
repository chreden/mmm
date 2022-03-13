#include "PlanetMiningBase.h"
#include "PlanetMiningBaseType.h"
#include "Type_Planet.h"

namespace mmm
{
	namespace
	{
		const std::size_t Function_SetPlanet = 0x004b7250;

		void PlanetMiningBase_SetPlanet( types::PlanetMiningBase* base,
										 types::Planet* planet )
		{
			(base->*memory_function<void (types::PlanetMiningBase::*)(types::Planet*)>(Function_SetPlanet))
					( planet );
		}
	}

	PlanetMiningBasePtr
	PlanetMiningBase::create( types::Entity* ent )
	{
		return PlanetMiningBasePtr( new PlanetMiningBase( static_cast<types::PlanetMiningBase*>( ent ) ) );
	}

	PlanetMiningBase::PlanetMiningBase( types::PlanetMiningBase* base )
		: Craft( base )
	{

	}

	types::PlanetMiningBase*
	PlanetMiningBase::getPlanetMiningBase() const
	{
		return static_cast<types::PlanetMiningBase*>( getEntity() );
	}

	void
	PlanetMiningBase::allocateReplacement( luabind::detail::object_rep* object )
	{
		entity_allocate_replacement<PlanetMiningBase>( object, boost::static_pointer_cast<PlanetMiningBase>( shared_from_this() ) );
	}

	EntityPtr
	PlanetMiningBase::getPlanet( ) const
	{
		return createEntityPtr( GetEntity<types::Entity>( getPlanetMiningBase()->m_planetHandle ) );
	}

	float
	PlanetMiningBase::getOrbitOmega() const
	{
		return getPlanetMiningBase()->m_orbital_omega;
	}

	int
	PlanetMiningBase::getNumHoldingBeams( ) const
	{
		return getPlanetMiningBase()->m_holdingBeamCount;
	}

	void
	PlanetMiningBase::setPlanet( EntityPtr ent ) 
	{
		if( ent )
		{
			if( ent->isType( Entity_Planet ) )
			{
				PlanetMiningBase_SetPlanet( getPlanetMiningBase(), 
											static_cast<types::Planet*>( ent->getEntity() ) );
			}
		}
		PlanetMiningBase_SetPlanet( getPlanetMiningBase(), 0 );
	}

	void
	PlanetMiningBase::setOrbitOmega( float value )
	{
		getPlanetMiningBase()->m_orbital_omega = value;
	}

	void
	PlanetMiningBase::setNumHoldingBeams( int value )
	{
		getPlanetMiningBase()->m_holdingBeamCount = value;
	}
}
