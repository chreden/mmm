#pragma once

namespace mmm
{
	namespace types
	{
		//I think this is the weapon used by the Jach'Eng class ship. Basically it
		//is never going to be used, but whatever.
		struct ShockwaveCannon :
			public ShockwaveExplosion
		{
			Vector3 edgeDirection1;
			Vector3 edgeDirection2;
			Vector3 centralDirection;
		};
	}
}
