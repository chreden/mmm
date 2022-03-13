#pragma once

#include "Type_ShipyardClass.h"

namespace mmm
{
	namespace types
	{
		struct StarbaseClass
			: public ShipyardClass
		{
			long					m_maxCrewGain;
			ResourceTransferData*	m_pTransferData;
			char*					dockingHardpoint;
		};
	}
}