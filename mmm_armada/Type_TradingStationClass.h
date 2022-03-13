#pragma once

#include "Type_MiningStationClass.h"

namespace mmm
{
	namespace types
	{
		struct TradingStationClass
			: public MiningStationClass
		{
			float					 m_cargoTransferRate;
			float					 m_percentTradeProfit;
			VectorAdapter<CargoDesc> m_cargoTypes;
		};
	}
}