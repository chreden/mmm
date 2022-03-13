#include "Type_ST3D_GraphicsEngine.h"

namespace mmm
{
	namespace types
	{
		namespace 
		{
			const std::size_t Address_ST3D_GraphicsEngine = 0x007ad508;
		}

		ST3D_GraphicsEngine*
		getGraphicsEngine()
		{
			return *reinterpret_cast<ST3D_GraphicsEngine**>( Address_ST3D_GraphicsEngine );
		}
	}
}
