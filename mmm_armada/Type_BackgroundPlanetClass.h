#pragma once

#include "Type_BackgroundObjectClass.h"

namespace mmm
{
	namespace types
	{
		struct ST3D_SpriteNodeData;

		struct BackgroundPlanetClass
			: public BackgroundObjectClass
		{
			ST3D_SpriteNodeData*	m_nimbus;			//Ignored
			float					rotationRate;		//Done
			float					crewModifier;		//Done
		};
	}
}
