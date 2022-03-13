#pragma once 

#include "Type_Producer.h"

namespace mmm
{
	namespace types
	{
		struct ResourceTransferInterface;

		struct MiningStation
			: public Producer
		{
			float					   m_nextResourceCheckTime;
			ResourceTransferInterface* m_pResourceTransferInterface;
		};
	}
}
