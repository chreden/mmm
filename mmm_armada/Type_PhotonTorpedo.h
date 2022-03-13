#pragma once

#include "Type_Missile.h"

namespace mmm
{
	namespace types
	{
		struct PhotonTorpedo
			: public Missile
		{
			ST3D_Colour m_photonColor;
		};
	}
}
