#pragma once

#include "OrdnanceType.h"

namespace mmm
{
	namespace types
	{
		struct Mine
			: public Ordnance
		{
			eMineStatus m_mineStatus;
		};
	}
}
