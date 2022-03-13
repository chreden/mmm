#pragma once

namespace mmm
{
	namespace types
	{
		struct ShockwaveExplosion :
			public Explosion
		{
			void*	m_virtual_light;		//VirtualLight
			void*	m_explosion_fx;			//ExplosionFX;
			int		whoCausedMe;
			int		teamThatCausedMe;
			float	m_timer;
			float	m_fullRadius;
			void*	m_mesh;					//ST3D_Mesh
		};
	}
}
