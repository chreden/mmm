#include "CargoShip_Internal.h"
#include "Type_CargoShip.h"

namespace mmm
{
	CargoShipPtr 
	CargoShip::create( types::Entity* entity )
	{
		return CargoShipPtr( new CargoShip( static_cast<types::CargoShip*>( entity ) ) );
	}

	CargoShip::CargoShip( types::CargoShip* cargoShip )
		: Craft( cargoShip )
	{

	}

	void
	CargoShip::allocateReplacement( luabind::detail::object_rep* obj )
	{
		entity_allocate_replacement<CargoShip>( obj, boost::static_pointer_cast<CargoShip>( shared_from_this() ) );
	}

	types::CargoShip* 
	CargoShip::getCargoShip( ) const
	{
		return static_cast<types::CargoShip*>( getEntity() );
	}

	EntityPtr
	CargoShip::getStartStation( ) const
	{
		return createEntityPtr( GetEntity<types::Entity>( getCargoShip()->m_startStation ) );
	}
	
	EntityPtr
	CargoShip::getDestinationStation( ) const
	{
		return createEntityPtr( GetEntity<types::Entity>( getCargoShip()->m_goalStation ) );
	}

	bool
	CargoShip::getIsTrading( ) const
	{
		return getCargoShip()->m_isTrading;
	}

	float
	CargoShip::getMaxCargo( ) const
	{
		return getCargoShip()->m_maxCargo;
	}

	eResource
	CargoShip::getNextResource() const
	{
		return getCargoShip()->m_nextCargoType;
	}

	float
	CargoShip::getCargoAmount() const
	{
		if( getCargoShip()->m_pGoods )
		{
			return getCargoShip()->m_pGoods->m_amtGoods;
		}
		return 0.0f;
	}

	eResource
	CargoShip::getResource() const
	{
		if( getCargoShip()->m_pGoods )
		{
			return getCargoShip()->m_pGoods->m_resource;
		}
		return RESOURCE_CREW;
	}

	std::string
	CargoShip::getCargoName( ) const
	{
		if( getCargoShip()->m_pGoods )
		{
			return getCargoShip()->m_pGoods->m_pCargoDesc->key;
		}
		return std::string();
	}

	bool
	CargoShip::getIsFull() const
	{
		if( getCargoShip()->m_pGoods )
		{
			return getCargoShip()->m_pGoods->m_full;
		}
		return false;
	}
}