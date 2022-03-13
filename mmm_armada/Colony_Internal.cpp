#include "Colony_Internal.h"
#include "Type_Colony.h"
#include "ColonyClass_Internal.h"
#include "Type_ColonyClass.h"

namespace mmm
{
	ColonyPtr 
	Colony::create( types::Entity* entity )
	{
		return ColonyPtr( new Colony( static_cast<types::Colony*>( entity ) ) );
	}

	Colony::Colony( types::Colony* colony )
		: Craft( colony )
	{

	}

	types::Colony*
	Colony::getColony() const
	{
		return static_cast<types::Colony*>( getEntity() );
	}

	EntityPtr
	Colony::getPlanet() const
	{
		return createEntityPtr( GetEntity<types::Entity>( getColony()->m_planetHandle ) );
	}

	int
	Colony::getColonists( ) const
	{
		return getColony()->m_colonists;
	}

	int
	Colony::getInitialColonists() const
	{
		return getColony()->m_initialColonists;
	}

	float
	Colony::getInitialPopulation() const
	{
		return getColony()->m_initialPopulation;
	}

	void
	Colony::setColonists( int value )
	{
		getColony()->m_colonists = value;
	}

	void
	Colony::setInitialColonists( int value )
	{
		getColony()->m_initialColonists = value;
	}

	void
	Colony::setInitialPopulation( float value )
	{
		getColony()->m_initialPopulation = value;
	}

	void 
	Colony::allocateReplacement( luabind::detail::object_rep* object )
	{
		entity_allocate_replacement<Colony>( object, boost::static_pointer_cast<Colony>( shared_from_this() ) );
	}
}
