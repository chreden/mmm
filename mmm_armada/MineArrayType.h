#pragma once

#include "Type_Craft.h"

namespace mmm
{
	namespace types
	{
		struct MineArray : public Craft
		{
			Vector3			m_home;
			int				m_target;
			eMineArrayState m_state;
		};
	}
}
