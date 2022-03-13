#pragma once

#include "Type_Entity.h"

namespace mmm
{
	namespace types
	{
		struct ExplosionClass;

		struct Explosion
			: public Entity
		{
			int				m_whoIsResponsibleForBlast;
			ExplosionClass* m_explosionClass;
			float			m_radius;
			bool			m_soundPlayed;
		};
	}
}
