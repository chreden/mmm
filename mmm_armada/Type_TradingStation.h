#pragma once

#include "MiningStationType.h"

namespace mmm
{
	namespace types
	{
		struct TradingStation
			: public MiningStation
		{
			eDockingState m_DockingState;				//Done
			Vector3		  m_rallyPoint;					//Done
			float		  m_ferengiTradingTime;			//Done
			int			  m_ferengiNowTradingHandle;	//Done
		};
	}
}
