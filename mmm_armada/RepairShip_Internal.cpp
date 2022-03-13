//Notes - in Fleet Operations it seems that the repair ship uses a weapon
//instead of just repairing via the class. This means I will either have to
//go via the carrier or just not support this for fleet ops, or say that
//they need to do it manually.

#include "RepairShip_Internal.h"
#include "RepairShipClass_Internal.h"
#include "Type_RepairShip.h"
#include "Type_RepairShipClass.h"
#include "MemRaider.h"

namespace mmm
{
	namespace
	{

	}

	RepairShipPtr 
	RepairShip::create( types::Entity* entity )
	{
		return RepairShipPtr( new RepairShip( static_cast<types::RepairShip*>( entity ) ) );
	}

	RepairShip::RepairShip( types::RepairShip* ship )
		: Craft( ship )
	{

	}

	types::RepairShip*
	RepairShip::getRepairShip() const
	{
		return static_cast<types::RepairShip*>( getEntity() );
	}

	EntityPtr 
	RepairShip::getRepairTarget( ) const
	{
		//Extracts the target from the repair ship process - this will eventually use the actual
		//process but for now just uses mem raider.
		const types::RepairShip* const ship = getRepairShip();
		return createEntityPtr( GetEntity<types::Entity>( memraider::MrNode( ship->aiProcess ).get<int>( 0x1ac ) ) );
	}

	void	 
	RepairShip::setRepairTarget( EntityPtr ent )
	{
		if( ent->isType( Entity_Craft ) )
		{
			getRepairShip()->m_pCraft = static_cast<types::Craft*>( ent->getEntity() );
		}
	}

	void
	RepairShip::allocateReplacement( luabind::detail::object_rep* obj )
	{
		entity_allocate_replacement<RepairShip>( obj, boost::static_pointer_cast<RepairShip>( shared_from_this() ) );
	}
}
