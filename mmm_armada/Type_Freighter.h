#pragma once

#include "Type_Craft.h"

namespace mmm
{
	namespace types
	{
		struct ST3D_Node;

		class Freighter 
			: public Craft
		{
		public:
			ST3D_Node*		m_ore_graphics_node;	
			float*			m_maxResource;			//Done
			float			m_resourceHeld;			//Done
			eResource		m_currentlyHolding;		//Done
			bool			m_droppingOff;			//Done
			int				m_resourceHandle;		//Done
			int				m_station;				//Done
			int				m_craftResource;		
			Vector3			m_craftResourcePos;		
		};
	}
}
