#include "RepairShipClass_Internal.h"
#include "Type_RepairShipClass.h"

namespace mmm
{
	RepairShipClassPtr 
	RepairShipClass::create( types::GameObjectClass* ptr )
	{
		return RepairShipClassPtr( new RepairShipClass( static_cast<types::RepairShipClass*>( ptr) ) );
	}

	RepairShipClass::RepairShipClass( types::RepairShipClass* ship )
		: CraftClass( ship )
	{

	}

	types::RepairShipClass*
	RepairShipClass::getRepairShipClass() const
	{
		return static_cast<types::RepairShipClass*>( getClass() );
	}

	float
	RepairShipClass::getRepairRate( ) const
	{
		return getRepairShipClass()->m_repairRate;
	}

	void
	RepairShipClass::setRepairRate( float value )
	{
		getRepairShipClass()->m_repairRate = value;
	}
}
