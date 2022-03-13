#pragma once

#include "MiningStationClass_Internal.h"

namespace mmm
{
	namespace types { struct TradingStationClass; }

	class TradingStationClass 
		: public MiningStationClass
	{
	public:
		explicit TradingStationClass( types::TradingStationClass* station );
	private:
		types::TradingStationClass* getTradingStationClass() const;
	};

	void tradingstationclass_register( lua_State* state );
}
