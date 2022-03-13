#pragma once

#include "Type_AreaEffectObjectClass.h"

namespace mmm
{
	namespace types
	{
		struct BlackHoleClass
			: public AreaEffectObjectClass
		{
			float m_gravityRadius;
			float m_eventRadius;
			float m_gravityForce;
			float m_rotation;
			float m_scaleSize;
		};
	}
}
