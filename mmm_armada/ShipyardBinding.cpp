#include "Shipyard_Internal.h"
#include "Wormhole.h"
#include "OrientedQueue.h"

namespace mmm
{
	void
	shipyard_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<Shipyard, Producer, EntityPtr>( "Shipyard" )
				.property( "rallyPoint", &Shipyard::getRallyPoint, &Shipyard::setRallyPoint )
				.property( "repairingShip", &Shipyard::getRepairingShip )
				.property( "repairQueue", &Shipyard::getRepairQueue )
		];
	}
}
