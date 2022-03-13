#pragma once

#include "OrdnanceType.h"

namespace mmm
{
	namespace types
	{
		struct Bullet 
			: public Ordnance
		{
			Vector3 startPos;
			Vector3 currentPos;
		};
	}
}
