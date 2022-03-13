#pragma once

#include "Type_CraftClass.h"

namespace mmm
{
	namespace types
	{
		struct ProducerClass
			: public CraftClass
		{
			GameObjectClass* buildItem[0xE];
			char*			 buildHardpoint;
		};
	}
}
