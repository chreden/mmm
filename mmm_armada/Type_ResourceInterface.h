#pragma once

namespace mmm
{
	namespace types
	{
		struct ResourceInterfaceClass
		{
			void*			m_pCfg;
			float*			m_amtResource;
			unsigned char	m_isInfinite;
			float			m_miningRate;
			unsigned char	m_canHaveOrbitalStation;
			float			m_trickleAmount;
			float			m_trickleMiningRate;
		};

		struct ResourceInterface
		{
			void*					m_vfptr;			
			ResourceInterfaceClass* pRIClass;			//	Not done
			GameObject*				m_pOwner;			//	N/A
			int						m_minerID;			//	Done
			int						m_orbitalID;		//	Done
			int						m_lastTimeMined;	//	Ignore
			bool					m_isInfinite;		//	Done
			float*					m_amtResource;		//	Done
		};
	}
}