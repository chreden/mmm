#include "Freighter_Internal.h"

namespace mmm
{
	void
	freighter_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<Freighter, Craft, EntityPtr>( "Freighter" )
				.property( "amount", &Freighter::getAmountCarried, &Freighter::setAmountCarried )
				.property( "resource", &Freighter::getResourceCarried, &Freighter::setResourceCarried )
				.property( "spaceRemaining", &Freighter::getSpaceRemaining )
				.property( "droppingOff", &Freighter::getDroppingOff )
				.property( "source", &Freighter::getResourceSource )
				.property( "station", &Freighter::getStation )
				.property( "maxAmount", &Freighter::getMaxAmountCurrent )
				.def( "getMaxAmount", &Freighter::getMaxAmount )
		];
	}
}
