#include "TradingStation.h"

namespace mmm
{
	void
	tradingstation_register( lua_State* state )
	{
		using namespace luabind;
		module(state)
		[
			class_<TradingStation, MiningStation, EntityPtr>( "TradingStation" )
				.property("dockingState", &TradingStation::getDockingState )
				.property("rallyPoint", &TradingStation::getRallyPoint, &TradingStation::setRallyPoint )
				.property("dockedFerengi", &TradingStation::getDockedFerengi )
				.scope
				[	class_<eDockingState>("DockingState")
						.enum_("constants")
						[
							value("JustDocked", JustDocked),
							value("LoadCargo", LoadCargo),
							value("UnloadCargo", UnloadCargo),
							value("Exit", Exit )
						]
				]
		];
	}
}