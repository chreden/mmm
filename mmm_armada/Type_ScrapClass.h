#pragma once

#include "Type_TerrainObjectClass.h"

namespace mmm
{
	namespace types
	{
		struct ScrapClass
			: public TerrainObjectClass
		{
			float m_rotation_speed;
		};
	}
}
