#pragma once

#include "VectorAdapter.h"

namespace mmm
{
	namespace types
	{
		struct Weapon
		{
			virtual ~Weapon() = 0;
			void*	weaponClass;
			void*	m_pOrdnanceClass;
			char	m_hardpointList[0xC];
			int		m_ownerHandle;
			Vector3 m_targetLocationPos;
			float	m_shotTimer;
			unsigned char m_triggered;
			unsigned char m_on;
			unsigned char m_isExtra;
			unsigned char m_isRemovable;
			void*		  m_pLoopSound;
			int			  m_multiWeaponFleetID;
			int			  m_targetHandle;
		};

		struct Carrier
		{
			virtual ~Carrier() = 0;
			GameObject*		m_pOwner;
			VectorAdapter<Weapon*> m_weaponList;
			Weapon*			m_pSelected;
			float			m_minRegularRange;
			float			m_maxRegularRange;
			float			m_minWeaponRange;
			float			m_maxWeaponRange;
			int				m_numRegularWeapons;
			int				m_numSpecialWeapons;
			unsigned char	m_hasArtillery;
			unsigned char	m_hasRestrictedFireArc;
			unsigned char	m_isEnabled;
			int				m_live;
		};
	}
}
