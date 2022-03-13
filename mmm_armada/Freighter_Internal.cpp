#include "Freighter_Internal.h"
#include "Type_Freighter.h"

namespace mmm
{
	namespace
	{
		const std::size_t Address_GetResourceSpaceRemaining	= 0x004b1800;
	}

	FreighterPtr 
	Freighter::create( types::Entity* entity )
	{
		return FreighterPtr( new Freighter( static_cast<types::Freighter*>( entity ) ) );
	}

	Freighter::Freighter( types::Freighter* freighter )
		: Craft( freighter )
	{

	}

	types::Freighter* 
	Freighter::getFreighter() const
	{
		return static_cast<types::Freighter*>( getEntity() );
	}

	eResource
	Freighter::getResourceCarried( ) const
	{
		return getFreighter()->m_currentlyHolding;
	}

	float
	Freighter::getSpaceRemaining() const
	{
		typedef float (types::Freighter::*MemFunction) ( eResource ) const;
		MemFunction function = memory_function< MemFunction >( Address_GetResourceSpaceRemaining );
		return (getFreighter()->*function)( getResourceCarried() );
	}

	float
	Freighter::getAmountCarried() const
	{
		return getFreighter()->m_resourceHeld;
	}

	float	  
	Freighter::getMaxAmount( eResource resource ) const
	{
		if( resource < 0 || resource > NUMBER_OF_RESOURCES )
		{
			return 0;
		}
		return getFreighter()->m_maxResource[resource];
	}

	float	  
	Freighter::getMaxAmountCurrent( ) const
	{
		return getFreighter()->m_maxResource[getResourceCarried()];
	}

	bool	  
	Freighter::getDroppingOff() const
	{
		return getFreighter()->m_droppingOff;
	}

	EntityPtr
	Freighter::getResourceSource() const
	{
		return createEntityPtr( GetEntity<types::Entity>( getFreighter()->m_resourceHandle ) );
	}

	EntityPtr 
	Freighter::getStation() const
	{
		return createEntityPtr( GetEntity<types::Entity>( getFreighter()->m_station ) );
	}

	void
	Freighter::setResourceCarried( eResource resource )
	{
		getFreighter()->m_currentlyHolding = resource;
	}

	void
	Freighter::setAmountCarried( float value )
	{
		getFreighter()->m_resourceHeld = value;
	}
	
	void
	Freighter::allocateReplacement( luabind::detail::object_rep* obj )
	{
		entity_allocate_replacement<Freighter>( obj, boost::static_pointer_cast<Freighter>( shared_from_this() ) );
	}
}