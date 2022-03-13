#pragma once

#include "Type_GameObject.h"

namespace mmm
{
	namespace types
	{
		struct CraftClass;
		
		struct ConstructionObject
			: public GameObject
		{
			CraftClass*		m_pBuildClass;
			int				m_rigHandle;
		};
	}
}
