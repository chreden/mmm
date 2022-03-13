#pragma once

namespace mmm
{
	namespace types
	{
		struct AiPath
		{
			int			pointCount;				//Done
			Vector3*	points;					//Done
			int			pathType; 
			float		asteroid_belt_speed;	
			int			m_nebula_type;
			int			me;						//Iterator (me)
			bool		m_pathPlanningInited;
			char*		m_pLabel;				//Done		
			char*		m_pDistances;
		};
	}
}
