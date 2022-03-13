#pragma once

#include "Type_AreaEffectObject.h"

namespace mmm
{
	namespace types
	{
		//Yes, its more complex than that but i just wanted the static cast.
		//Fix later.
		struct Wormhole : public AreaEffectObject
		{
			virtual ~Wormhole( ) = 0;

			void* m_pInputQueue;
			void* m_pOutputQueue;
			GateStatus m_wormholeState;
			void* m_pGlow;
			Wormhole* m_pWormholePartner;
			int m_ownerTeam;
			int m_ownerEntity;
			float m_disableTimer;
			float m_currentScale;
			float m_closeTime;
			void* m_pStuffedCraft;
			int m_deleteBuddyHandle;
			int m_shipyardHandle;
			bool m_deleteOnTransport;
			bool m_expireOnClose;
			char m_pDisplayName[0x80];
		};
	}
}
