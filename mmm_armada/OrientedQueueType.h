#pragma once

#include "SplineQueueType.h"

namespace mmm
{
	enum eQueueSide 
	{
		QUEUE_SIDE_CENTER = 0x0,
		QUEUE_SIDE_LEFT = 0x1,
		QUEUE_SIDE_RIGHT = 0x2,
		QUEUE_SIDE_BOTTOM = 0x4,
		QUEUE_SIDE_TOP = 0x8,
	};

	namespace types
	{
		struct OrientedQueue
			: public SplineQueue
		{
			eQueueSide		m_queueSide;
			Vector3			m_direction;		//Done
			Vector3			m_endOffset;		//Done
			float			m_queueLength;		
			bool			m_nebulaInWay;
			float			m_nebulaDistance;
			float			m_nebulaSize;
		};
	}
}
