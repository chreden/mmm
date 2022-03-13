#pragma once

#include "Type_TerrainObject.h"

namespace mmm
{
	namespace types
	{
		struct UtritiumBall
			: public TerrainObject
		{
			float m_time_left;
			float m_currentScaleCount;
			int	  m_ownerHandle;
		};
	}
}
