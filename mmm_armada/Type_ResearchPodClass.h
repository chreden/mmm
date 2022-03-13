#pragma once

#include "Type_CraftClass.h"

namespace mmm
{
	namespace types
	{
		struct ResearchPodClass 
			: public CraftClass
		{
			bool	m_isShipUpgrade;
			int		m_upgradeLevel;
			int		m_upgradeSystem;
			float	m_upgradeMultiplier;
			bool	m_isUpgrade;
		};
	}
}
