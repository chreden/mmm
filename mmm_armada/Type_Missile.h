#pragma once

#include "OrdnanceType.h"

namespace mmm
{
	namespace types
	{
		struct Missile
			: public Ordnance
		{
			float turnLim2;
			float seekTimer;
			Vector3 omega;
		};
	}
}
