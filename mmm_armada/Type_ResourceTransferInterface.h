#pragma once

namespace mmm
{
	namespace types
	{
		struct ResourceTransferData
		{
			float m_biomatterConversionRates[6];
			float m_transferRates[6];
		};

		struct OrientedQueue;

		struct ResourceTransferInterface
		{
			void*					vfptr;					//Done			
			int						m_dockedShip;			//Done
			types::Craft*			m_owner;				//N/A
			OrientedQueue*			m_mining_queue;			//Done
			void*					m_exit_queue;			//Ignore
			void*					m_dockingHardpoint;		//Ignore
			ResourceTransferData*	m_pTransferData;		//NotDone
		};
	}
}
