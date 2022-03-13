#pragma once

#include "Type_TerrainObjectClass.h"

namespace mmm
{
	namespace types
	{
		struct UtritiumBallClass
			: public TerrainObjectClass
		{
			long	m_damageValue;			//Done
			float	m_lifeTimer;			//Done
			float	m_radius;				//Done
			float	m_scalingStepSize;			
			float	m_scalingCount;			
			float	m_rotation;				//Done
		};
	}
}
