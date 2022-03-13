#pragma once

#include "Type_ProducerClass.h"

namespace mmm
{
	namespace types
	{
		struct ResearchStationClass 
			: public ProducerClass
		{
			VectorAdapter<char*> m_podHardpointNames;
			GameObjectClass*	 m_pSecondaryBuildItems[14];
			bool				 m_buildItemReserved[14];
		};
	}
}
