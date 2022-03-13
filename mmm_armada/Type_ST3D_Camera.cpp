#include "Type_ST3D_Camera.h"

namespace mmm
{
	namespace types
	{
		namespace
		{
			const std::size_t Address_CurrentCamera = 0x00765010;
		}

		ST3D_Camera* 
		getCurrentCamera()
		{
			return *reinterpret_cast<types::ST3D_Camera**>( Address_CurrentCamera );
		}
	}
}
