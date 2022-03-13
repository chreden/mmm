#pragma once

#include "ListAdapter.h"

namespace mmm
{
	namespace types
	{
		struct Queue
		{
			void*				_vfptr;					//Virtual pointer
			ListAdapter<int>	m_idList;				//Entries
			Vector3				m_offset;				//
			GameObject*			m_attachment;			//
			float				m_inactiveLength;		//
		};
	}
}
