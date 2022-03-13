#include "Shipyard_Internal.h"
#include "Type_Shipyard.h"
#include "Type_Entity.h"
#include "WormholeType.h"
#include "Wormhole.h"
#include "OrientedQueue.h"

namespace mmm
{
	ShipyardPtr 
	Shipyard::create( types::Entity* entity )
	{
		return ShipyardPtr( new Shipyard( static_cast<types::Shipyard*>( entity ) ) );
	}

	Shipyard::Shipyard( types::Shipyard* shipyard )
		: Producer( shipyard )
	{

	}

	types::Shipyard*
	Shipyard::getShipyard( ) const
	{
		return static_cast<types::Shipyard*>( getEntity() );
	}

	EntityPtr
	Shipyard::getWormhole( ) const
	{
		return createEntityPtr( getShipyard()->m_pWormhole );
	}

	EntityPtr
	Shipyard::getRepairingShip( ) const
	{
		return createEntityPtr( GetEntity<types::Entity>( getShipyard()->m_dockedShip ) );
	}

	const Vector3
	Shipyard::getRallyPoint( ) const
	{
		return getShipyard()->m_rallyPoint;
	}

	OrientedQueuePtr
	Shipyard::getRepairQueue() const
	{
		return OrientedQueue::create( static_cast<types::OrientedQueue*>( getShipyard()->m_pRepairQueue ) );
	}

	void
	Shipyard::setWormhole( EntityPtr wormhole )
	{
		if( wormhole || !wormhole->isType( Entity_Wormhole ) )
		{
			return;
		}
		getShipyard()->m_pWormhole = static_cast<types::Wormhole*>(wormhole->getEntity());
	}

	void
	Shipyard::setRallyPoint( const Vector3& point )
	{
		getShipyard()->m_rallyPoint = point;
	}

	void
	Shipyard::allocateReplacement( luabind::detail::object_rep* obj )
	{
		entity_allocate_replacement<Shipyard>( obj, boost::static_pointer_cast<Shipyard>( shared_from_this() ) );
	}
}
