#include "Type_GameObjectClass.h"

namespace mmm
{
	namespace types
	{
		bool 
		isGameObjectClass( const types::GameObjectClass* const ptr )
		{
			return ptr;
		}

		bool 
		isCraftClass( const types::GameObjectClass* const ptr )
		{
			return ptr && ptr->m_objType & Type_Craft;
		}

		bool 
		isCargoShipClass( const types::GameObjectClass* const ptr )
		{
			return ptr && ptr->m_objType & Type_CargoShip;
		}

		bool 
		isColonyClass( const types::GameObjectClass* const ptr )
		{
			return ptr && std::string(typeid(*ptr).raw_name()) == ".?AVColonyClass@@";
		}

		bool 
		isFreighterClass( const types::GameObjectClass* const ptr )
		{
			return ptr && ptr->m_objType & Type_Freighter;
		}

		bool 
		isMineArrayClass( const types::GameObjectClass* const ptr )
		{
			return ptr && 
				   std::string(typeid(*ptr).raw_name()) == ".?AVMineArrayClass@@";
		}

		bool 
		isPlanetMiningBaseClass( const types::GameObjectClass* const ptr )
		{
			return ptr && std::string(typeid(*ptr).raw_name()) == ".?AVPlanetMiningBaseClass@@";
		}

		bool 
		isRepairShipClass( const types::GameObjectClass* const ptr )
		{
			return ptr && std::string(typeid(*ptr).raw_name()) == ".?AVRepairShipClass@@";
		}

		bool 
		isResearchPodClass( const types::GameObjectClass* const ptr )
		{
			return ptr && ptr->m_objType & Type_ResearchPod;
		}

		bool 
		isScavengerClass( const types::GameObjectClass* const ptr )
		{
			return ptr && ptr->m_objType & Type_Scavenger;
		}

		bool 
		isSensorArrayClass( const types::GameObjectClass* const ptr )
		{
			return ptr && ptr->m_objType & Type_SensorArray;
		}
		
		bool 
		isProducerClass( const types::GameObjectClass* const ptr )
		{
			return ptr && ptr->m_objType & Type_Producer;
		}

		bool 
		isConstructionRigClass( const types::GameObjectClass* const ptr )
		{
			return ptr && ptr->m_objType & Type_Rig;
		}

		bool 
		isEvolverClass( const types::GameObjectClass* const ptr )
		{
			return ptr && std::string(typeid(*ptr).raw_name()) == ".?AVEvolverClass@@";
		}

		bool 
		isPlanetClass( const types::GameObjectClass* const ptr )
		{
			return ptr && std::string(typeid(*ptr).raw_name()) == ".?PlanetClass@@";
		}

		bool 
		isResearchStationClass( const types::GameObjectClass* const ptr )
		{
			return ptr && ptr->m_objType & Type_ResearchStation;
		}

		bool 
		isShipyardClass( const types::GameObjectClass* const ptr )
		{
			return ptr && ptr->m_objType & Type_Shipyard;
		}

		bool 
		isStarbaseClass( const types::GameObjectClass* const ptr )
		{
			return ptr && ptr->m_objType & Type_Starbase;
		}
		
		bool 
		isMiningStationClass( const types::GameObjectClass* const ptr )
		{
			return ptr && ptr->m_objType & Type_MiningStation; 
		}

		bool 
		isTradingStationClass( const types::GameObjectClass* const ptr )
		{
			return ptr && std::string(typeid(*ptr).raw_name()) == ".?AVTradingStationClass@@";
		}

		bool 
		isTerrainObjectClass( const types::GameObjectClass* const ptr )
		{
			return ptr && isAsteroidFieldClass( ptr ) || 
						  isBackgroundObjectClass( ptr ) ||
						  isScrapClass( ptr ) ||
						  isUtritiumBallClass( ptr ) ||
						  isLatinumNebulaClass( ptr ) ||
						  isAreaEffectObjectClass( ptr );
		}

		bool 
		isAreaEffectObjectClass( const types::GameObjectClass* const ptr )
		{
			return isWormholeClass( ptr )  ||
				   isNebulaClass( ptr )	  ||
				   isBlackholeClass( ptr ) ||
				   isIonStormClass( ptr );
		}

		bool 
		isBlackholeClass( const types::GameObjectClass* const ptr )
		{
			return ptr && ptr->m_objType & Type_Blackhole;
		}

		bool 
		isIonStormClass( const types::GameObjectClass* const ptr )
		{
			return ptr && ptr->m_objType & Type_IonStorm;
		}

		bool 
		isNebulaClass( const types::GameObjectClass* const ptr )
		{
			return ptr && ptr->m_objType & Type_Nebula;
		}

		bool 
		isWormholeClass( const types::GameObjectClass* const ptr )
		{
			return ptr && ptr->m_objType & Type_Wormhole;
		}

		bool 
		isAsteroidFieldClass( const types::GameObjectClass* const ptr )
		{
			return ptr && ptr->m_objType & Type_AsteroidField;
		}

		bool 
		isBackgroundObjectClass( const types::GameObjectClass* const ptr )
		{
			return ptr && ptr->m_objType & Type_BackgroundObject;
		}

		bool 
		isBackgroundPlanetClass( const types::GameObjectClass* const ptr )
		{
			return ptr && std::string(typeid(*ptr).raw_name()) == ".?AVBackgroundPlanetClass@@";
		}
		
		bool 
		isLatinumNebulaClass( const types::GameObjectClass* const ptr )
		{
			return ptr && std::string(typeid(*ptr).raw_name()) == ".?AVLatinumNebulaClass@@";
		}

		bool 
		isScrapClass( const types::GameObjectClass* const ptr )
		{
			return ptr && std::string(typeid(*ptr).raw_name()) == ".?AVScrapClass@@";;
		}

		bool 
		isUtritiumBallClass( const types::GameObjectClass* const ptr )
		{
			return ptr && std::string(typeid(*ptr).raw_name()) == ".?AVUtritiumBallClass@@";
		}

		bool 
		isConstructionObjectClass( const types::GameObjectClass* const ptr )
		{
			return ptr && ptr->m_objType & Type_ConstructionObject;
		}
	}
}