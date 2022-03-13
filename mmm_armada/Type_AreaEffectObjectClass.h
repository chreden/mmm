#pragma once

#include "Type_TerrainObjectClass.h"

namespace mmm
{
	namespace types
	{
		struct AreaEffectObjectClass
			: public TerrainObjectClass
		{
			float m_radius;
		};
	}
}
