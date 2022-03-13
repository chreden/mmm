#pragma once

#include "SObjectType.h"

namespace mmm
{
	namespace types
	{
		struct GameObject;

		struct AiProcess : public SObject
		{
			class AiMission* fMission;
			GameObject*		 fOwner;
			bool			 exited;
		};
	}
}