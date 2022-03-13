#pragma once

#include "OrdnanceType.h"

namespace mmm
{
	namespace types
	{
		struct BeamToggle
			: public Ordnance
		{
			Vector3 startPos;
			Vector3 endPos;
		};
	}
}
