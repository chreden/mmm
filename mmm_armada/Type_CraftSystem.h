#pragma once

#include "VectorAdapter.h"

namespace mmm
{
	namespace types
	{
		struct ST3D_Node;

		struct CraftSystem
		{
			bool					  active;					//	Done
			bool					  permanentDisable;			//	Done
			long					  maxHitPoints;				//	Done
			float					  hitPercent;				//	Not Done
			float					  adjustedHitPercent;		//	Not Done
			float					  crewLoss;					//	Not Done
			float					  repairTime;				//	Not Done
			double					  fHitPoints;				//	Done
			float					  sparkTime;				//	Ignore
			float					  sparkTimeElapsed;			//	Ignore
			float					  disableTimeLeft;			//	Not Done
			VectorAdapter<ST3D_Node*>* targetHardpoints;		//	Ignore
		};
	}
}
