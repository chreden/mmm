#include "TradingStationClass_Internal.h"

namespace mmm
{
	void
	tradingstationclass_register( lua_State* state )
	{
		using namespace luabind;
		module(state)
		[
			class_<TradingStationClass, MiningStationClass, GameObjectClassPtr>( "TradingStationClass" )
		];
	}
}
