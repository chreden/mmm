#include "Planet_Internal.h"
#include "Type_Planet.h"
#include "Race_Internal.h"

namespace mmm
{
	namespace
	{
		const std::size_t Address_GetMaxPopulation	=	0x004b5550;
		const std::size_t Address_GetPopulation		=	0x004b5960;
		const std::size_t Address_SetPopulation		=	0x004b5970;
	}

	PlanetPtr
	Planet::create( types::Entity* entity )
	{
		return PlanetPtr( new Planet( static_cast<types::Planet*>( entity ) ) );
	}

	Planet::Planet( types::Planet* planet )
		: Producer( planet )
	{

	}

	EntityPtr 
	Planet::getColonyShip() const
	{
		return createEntityPtr( GetEntity<types::Entity>( getPlanet()->m_colonyShip ) );
	}

	float 
	Planet::getMaxPopulation( ) const
	{
		typedef float (types::Planet::*MemFunction)( ) const;
		MemFunction function = memory_function< MemFunction >( Address_GetMaxPopulation );
		return (getPlanet()->*function)( );
	}

	float 
	Planet::getPopulation( ) const
	{
		typedef float (types::Planet::*MemFunction) ( ) const;
		MemFunction function = memory_function< MemFunction >( Address_GetPopulation );
		return (getPlanet()->*function)( );
	}

	void
	Planet::setPopulation( float value )
	{
		typedef void (types::Planet::*MemFunction) ( float );
		MemFunction function = memory_function< MemFunction >( Address_SetPopulation );
		(getPlanet()->*function)(value);
	}

	bool	 
	Planet::getHasShields() const
	{
		return getPlanet()->m_builtShields;
	}

	eCivPopulationLevel 
	Planet::getPopulationLevel() const
	{
		return getPlanet()->m_populationLevel;
	}

	RacePtr	 
	Planet::getOldRace() const
	{
		return Race::create( getPlanet()->m_pOldRace );
	}

	types::Planet* 
	Planet::getPlanet() const
	{
		return static_cast<types::Planet*>( getEntity() );
	}

	void
	Planet::allocateReplacement( luabind::detail::object_rep* obj )
	{
		entity_allocate_replacement<Planet>( obj, boost::static_pointer_cast<Planet>( shared_from_this() ) );
	}
}
