#pragma once

#include "Type_Craft.h"

namespace mmm
{
	namespace types
	{
		struct BuildQueueItem;
		class Producer : public Craft
		{
		public:
			GameObjectClass** m_ppBuildItems;			 //	Done
			GameObjectClass*  m_pBuildClassCurrent;		 //	Not done					
			void*			  m_pBuildLocation;			 //	Ignore
			float			  m_buildDoneTime;			 //	Done
			float			  m_buildShotTime;			 //	Not done					
			float			  m_totalBuildTime;			 //	Not done				
			int				  m_constructionID;			 //	Not done					
			int				  m_previousShipBuilt;		 //	Done
			BuildQueueItem*	  m_pBuildQueue;			 //	BuildQueueItem				
			int				  m_buildQueueCount;		 //	Done						
			GameObjectClass*  m_pBuildList[0xA];		 //	Done
			int				  m_buildId;				 //	Not done
			void*			  m_pBuildPositionInterface; //	BuildPositionInterface 
			int				  m_buildQueueNextId;		 //	Not done
		};
	}
}
