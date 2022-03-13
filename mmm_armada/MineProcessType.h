#pragma once

#include "AiProcessType.h"

namespace mmm
{
	namespace types
	{
		struct MineProcess : public AiProcess
		{
			Vector3 m_startingPoint;
			float	m_actionTimer;
		};
	}
}
