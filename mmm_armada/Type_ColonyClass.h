#pragma once

#include "Type_CraftClass.h"

namespace mmm
{
	namespace types
	{
		struct ColonyClass
			: public CraftClass
		{
			//Seriously have no idea what that is. Doesn't seem to be
			//that important.
			int m_cleansingWeaponIndex;
		};
	}
}
