#pragma once

#include "OrdnanceType.h"

namespace mmm
{
	namespace types
	{
		struct Beam 
			: public Ordnance
		{
			Vector3			m_startPos;					//Done
			Vector3			m_endPos;					//Done
			Vector3			m_offsetPos;
			float			m_noTargetLifeTimer;
			unsigned char	m_explosionEffectCreated;
			unsigned char	m_hadTarget;
			int				m_firstShieldID;
			int				m_secondShieldID;
		};
	}
}
