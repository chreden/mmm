#pragma once

#include "Type_GameObject.h"

namespace mmm
{
	namespace types
	{
		struct CraftSystem;

		struct Craft 
			: public GameObject
		{
		public:
			virtual ~Craft() = 0;
			
			//Statics
			
			static std::vector<Craft*> craftList;
			static float s_timePerSpeedSimulationStep;
			static float s_timePerOmegaSimulationStep;
			static void* objectRange;
			
			//Instance variables.

			Vector3 lastAvoidanceForce;
			int m_queueStage;
			int m_queueDestination;
			unsigned char m_canRepair;
			unsigned char requestDeque;
			void* pQueuePosition; //make into a queueposition*
			void* m_virtual_light; //make into Virtual light prt?
			void* m_transport_fx; //make into Transport FX*
			unsigned char m_blockingConstruction;
			void* m_pControls; //ccraftconrol *
			void* m_pRecrewInterface;
			float m_timer;
			unsigned char m_inSpecialForces;
			unsigned char m_countAgainstBuildTotalEvenInSpecialForces;
			unsigned char m_isTransporting;
			unsigned char m_derelict;
			float m_curShieldDelay;
			float m_maxCrew;
			float m_curShields;														//Done
			float m_maxShields;														//Done
			float m_shieldProjections;
			float m_transportDelay;
			int m_transportDestination;	//Ship id?	
			float m_curCrew;														//Done
			CraftSystem* m_pCraftSystem; //Craft system
			float m_hullHitPercent;
			float m_crewHitPercent;
			float m_boardingPartyMultiplier;
			float m_percentNebulaWarn;
			int m_battleID;
			void* m_landmark; //battle Landmark
			float m_manheimTimer;
			float m_shieldDisabledLastValue;
			float m_selfDestructRadius;
			int m_shieldCollapseID;
			Vector3 m_blackHoleCenter;
			int m_nameIndex;
			char* m_pCraftName;														//Done
			unsigned char m_blackHoleDeath;
			unsigned char m_shieldDisabledLastFrame;
			unsigned char m_manheimState;
			unsigned char m_inNebula;
			unsigned char m_canBeDerelictEvenIfCannotDie;
			unsigned char m_canBeDecommissioned;
			unsigned char m_dying;
			int m_AIFleet;
			void* m_pAIFleet;//AIFleet
			int m_strategicGoal;//GAOL TYPE strategic goal
			int m_decommissionID;
			float m_leftOverExplosion;
			float m_recycleTimer;
			float m_enhancedCloakTime;
			float m_warpFraction;
			float m_warpScale;
			int m_originalTeam;
		};
	}
}
