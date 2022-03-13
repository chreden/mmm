#include "CargoShip_Internal.h"

namespace mmm
{
	void
	cargoship_register( lua_State* state )
	{
		using namespace luabind;
		module(state)
		[
			class_<CargoShip, Craft, EntityPtr>("CargoShip")
				.property("cargoAmount", &CargoShip::getCargoAmount )
				.property("cargoName", &CargoShip::getCargoName )	
				.property("currentCargo", &CargoShip::getResource )
				.property("destinationStation", &CargoShip::getDestinationStation )
				.property("full", &CargoShip::getIsFull )
				.property("maxCargo", &CargoShip::getMaxCargo )
				.property("nextCargo", &CargoShip::getNextResource )
				.property("startStation", &CargoShip::getStartStation )
				.property("trading", &CargoShip::getIsTrading )
		];
	}
}