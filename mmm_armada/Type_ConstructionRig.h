#pragma once

#include "Type_Producer.h"

namespace mmm
{
	namespace types
	{
		struct ConstructionRig
			: public Producer
		{
			int m_workerBeeID;
			int m_numberOfBeesOnboard;
			int m_constructionObjectID;
		};
	}
}
