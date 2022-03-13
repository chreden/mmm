#pragma once

#include "Type_Producer.h"

namespace mmm
{
	namespace types
	{
		struct Wormhole;

		class Shipyard :
			public Producer
		{
		public:
			void*		m_pRepairQueue;			//Done
			void*		m_pExitRepairQueue;		//Ignore
			void*		m_pExitBuildQueue;		//Ignore
			int			m_dockedShip;			//Done
			void*		m_pRepairHardpoint;		//ST3D_Node
			Wormhole*	m_pWormhole;			//Ignore
			Vector3		m_rallyPoint;			//Done	
			void*		m_pRepairSound;			//Audio sound 3d
		};
	}
}
