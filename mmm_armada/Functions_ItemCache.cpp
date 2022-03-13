#include "Functions_ItemCache.h"

namespace mmm
{
	namespace functions
	{
		namespace 
		{
			static const std::size_t Address_InitItemCache = 0x00659b50;
		}

		void
		itemInitCache( )
		{
			memory_function<void (*)()>(Address_InitItemCache)();
		}
	}
}
