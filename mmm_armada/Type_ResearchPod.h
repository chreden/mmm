#pragma once

#include "Type_Craft.h"

namespace mmm
{
	namespace types
	{
		struct ResearchStation;

		struct ResearchPod
			: public Craft
		{
			class ResearchStation* researchStation;		//Done
			class cPrjID* m_pAssimWeaponID;
		};
	}
}
