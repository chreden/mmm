#pragma once

#include "Type_Beam.h"

namespace mmm
{
	namespace types
	{
		struct Phaser 
			: public Beam
		{
			ST3D_Colour m_phaserColor;
		};
	}
}
