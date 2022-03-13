#pragma once

#include "Type_ProducerClass.h"

namespace mmm
{
	namespace types
	{
		struct ResourceTransferData;

		struct MiningStationClass
			: public ProducerClass
		{
			char					freighterName[0x10];
			char					dockingHardpoint[0x10];
			ST3D_Node*				glowNode;
			ResourceTransferData*	m_pTransferData;
			float					m_checkValidResourceInterval;
		};
	}
}
