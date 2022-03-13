#pragma once

#include "Type_Bullet.h"

namespace mmm
{
	namespace types
	{
		struct PulsePhaser
			: public Bullet
		{
			ST3D_Colour m_phaserColour;
		};
	}
}
