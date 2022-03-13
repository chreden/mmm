#include "RepairShip_Internal.h"

namespace mmm
{
	void
	repairship_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<RepairShip, Craft, EntityPtr>( "RepairShip" )
				.property("repairTarget", &RepairShip::getRepairTarget, &RepairShip::setRepairTarget )
		];
	}
}
