#include "RepairShipClass_Internal.h"

namespace mmm
{
	void
	repairshipclass_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<RepairShipClass, CraftClass, GameObjectClassPtr>( "RepairShipClass" )
				.property("repairRate", &RepairShipClass::getRepairRate, &RepairShipClass::setRepairRate )
		];
	}
}