#pragma once

#include "Type_ProducerClass.h"

namespace mmm
{
	namespace types
	{
		enum eQueueSize
		{
			//What is in this?
		};

		struct ShipyardClass
			: public ProducerClass
		{
			char		repairHardpoint[0xA];
			bool		hasRepairFacility;
			bool		hasDecomissionfFacility;
			bool		buildAnimation;
			bool		repairAnimation;
			eQueueSize	m_repairSide;
			ST3D_Node*	fixNode;
			float		m_dilithiumRecyclingFraction;
			float		m_metalRecyclingFraction;
			cPrjID		m_wormhole;
			bool		m_alwaysComputeRallyPoint;
			float		m_recycleExchangeRate;
		};
	}
}
