#pragma once

#include "Type_AreaEffectObject.h"

namespace mmm
{
	namespace types
	{
		struct ST3D_Node;

		struct IonStorm : public AreaEffectObject
		{
			enum StormState
			{
				Closed = 0,
				Closing, 
				Open, 
				Opening
			};

			StormState  m_stormState;
			float		m_timeLeft;
			float		m_currentScaleCount;
			ST3D_Node*	m_startNode;
		};
	}
}
