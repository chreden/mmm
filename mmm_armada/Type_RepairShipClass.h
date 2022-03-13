#pragma once

#include "Type_CraftClass.h"

namespace mmm
{
	namespace types
	{
		struct RepairShipClass
			: public CraftClass
		{
			float m_repairRate;
		};
	}
}
