#include "TradingStationClass_Internal.h"
#include "Type_TradingStationClass.h"

namespace mmm
{
	TradingStationClass::TradingStationClass( types::TradingStationClass* station )
		: MiningStationClass( station )
	{

	}

	types::TradingStationClass* 
	TradingStationClass::getTradingStationClass() const
	{
		return static_cast<types::TradingStationClass*>( getClass() );
	}
}
