#pragma once

#include "Type_Producer.h"

namespace mmm
{
	namespace types
	{
		struct CocoonInstance;

		struct Evolver
			: public Producer
		{
			CocoonInstance* m_pCocoon;				
			float			m_buildFrac;			//Done (RW)		
			void*			m_pRandomSequence;		//dynarray<int>*
			float			m_shotDirectorRadius;	
			Vector3			m_buildStartLoc;		
		};
	}
}
