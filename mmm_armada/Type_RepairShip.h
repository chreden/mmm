#pragma once

#include "Type_Craft.h"

namespace mmm
{
	namespace types
	{
		struct RepairShip
			: public Craft
		{
			Craft* m_pCraft;
		};
	}
}
