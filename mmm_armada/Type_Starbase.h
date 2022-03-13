#pragma once

#include "Type_Shipyard.h"

namespace mmm
{
	namespace types
	{
		struct ResourceTransferInterface;

		struct Starbase :
			public Shipyard
		{
		public:
			ResourceTransferInterface* m_pResourceTransferInterface; //thats all it has...
		};
	}
}