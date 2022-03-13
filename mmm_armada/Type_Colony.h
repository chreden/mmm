#pragma once

#include "Type_Craft.h"

namespace mmm
{
	namespace types
	{
		struct Colony
			: public Craft
		{
			int		m_planetHandle;
			int		m_colonists;
			int		m_initialColonists;
			float	m_initialPopulation;
		};
	}
}
