#pragma once

namespace mmm
{
	namespace types
	{
		struct FireballExplosion
			: public Explosion
		{
			char	m_dbName[0x20];
			float	m_length;
			unsigned char m_hasShockwave;
			cPrjID m_shockwaveID;
			float	m_shockwaveDelay;
			float	m_shockwaveMinimumRadius;
			int		m_blameTheShooter;
		};
	}
}
