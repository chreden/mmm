#pragma once

#include "Type_Bullet.h"

namespace mmm
{
	namespace types
	{
		struct Artillery 
			: public Bullet
		{
			ST3D_Colour m_photonColor;
		};
	}
}
