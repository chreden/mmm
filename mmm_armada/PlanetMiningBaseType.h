#pragma once

#include "Type_Craft.h"

namespace mmm
{
	namespace types
	{
		struct PlanetMiningBase
			: public Craft
		{
			int		m_planetHandle;
			float	m_orbital_omega;
			int		m_holdingBeamCount;
		};
	}
}
