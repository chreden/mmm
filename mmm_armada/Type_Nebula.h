#pragma once

#include "Type_AreaEffectObject.h"

namespace mmm
{
	namespace types
	{
		struct AiPath;
		
		struct Nebula : public AreaEffectObject
		{
			virtual ~Nebula( ) = 0;

			AiPath* m_nebulaFieldPath;
			float	m_timeLeft;
			double	m_stretch_time;
			double	m_time_step;
			float	delta_roll;
			float	delta_pitch;
			float	delta_yaw;
			void*	m_glow;	//st3d_light (max)
			bool	m_nebulaCull;
			float	m_cullingInverseDist2;
			Vector3	m_cullingPos;
			float	m_cullingRadius;
			float	m_cullingFrontDist;
			float	m_cullingAverageIntensity;
			float	m_cullingAlpha;
			bool	m_canWeBuildInHere;
		};
	}
}
