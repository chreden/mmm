#pragma once

#include "Type_Producer.h"

namespace mmm
{
	namespace types
	{
		struct cPrjID;
		struct ST3D_Node;

		struct ResearchStation
			: public Producer
		{
			int						m_numberOfPods;					//Done
			GameObject**			m_ppPods;						//Done
			ST3D_Node**				m_ppPodHardpoints;
			GameObject**			m_pUpgrade;
			bool					m_podSpaceAvailable;
			GameObjectClass **		m_ppSecondaryBuildItems;
			GameObject*				m_pPrimaryPod;
			int						m_constructionIndex;
			bool					m_currentPodAssimilated;
			cPrjID*					m_pCurrentWeapon;
		};
	}
}
