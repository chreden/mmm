#pragma once

#include "VectorAdapter.h"

namespace mmm
{
	namespace types
	{
		struct WeaponClass;
		struct ST3D_Sprite;
		struct ST3D_Database;
		struct cPrjID;
		struct ResourceInterfaceClass;

		struct SPHERE
		{
			Vector3 origin;
			float	radius;
		};

		struct GameObjectClass
		{
			enum AnimationType
			{
				AnimateNever,
				AnimateForwardUponBuild,
				AnimateLoopedUponBuild,
				AnimateSpecialTrigger
			};
				
			virtual ~GameObjectClass();
				
			void*		m_light; //ST3D_Light
			Matrix34	m_object_to_shield;
			Matrix34	m_shield_to_object;
			float		buildTime;

			static int	s_class_count;

			int				 m_class_num;
			unsigned long	 sig;
			char*			 label;									//	Done
			GameObjectClass* proto;
			char*			 m_sod_filename;
			long			 m_dilithium_cost;
			long			 m_crewCost;
			long			 m_officerCost;
			long			 m_latinumCost;
			long			 m_metalCost;
			long			 m_biomatterCost;
			AnimationType	 animation;
			char			 m_weldingSpriteName[0x20];
			float			 m_weldingSpeed;
			float			 m_weldingAnimSpeed;
			float			 m_weldingRadius;
			float			 maxHealth;
			long			 maxSpecialEnergy;						// Done
			char*			 pHotkeyLabel;
			char			 unitString[0x40];						// Done
			char*			 overrideLabel;
			char			 m_ambientSound[0x20];
			float			 m_ambientMinimumFactor;
			float			 m_ambientMaximumFactor;
			VectorAdapter<WeaponClass*> weaponList;
			VectorAdapter<char*>		hardpointList;
			char			 aiName[0x20];							
			float			 collisionRadius;
			bool			 hasMapSize;
			long			 mapSize;
			ST3D_Sprite*	 map_sprite;
			ST3D_Sprite*	 map_icon;
			float			 shieldPad;
			char*			 infoText;
			bool			 isAlwaysHidden;
			bool			 avoidMe;
			bool			 buildBelowCombatArea;
			float			 distanceBelowGrid;
			int				 avoidanceClass;
			float			 m_scaleSOD;							

			//This is here - static, so vector adapter won't work. Will have to get by mem pointer.
			//static VectorAdapter<GameObjectClass*> classlist;

			float			 m_directorRadiusScale;
			Race*		     m_pRace;
			char*			 m_tooltip;
			char*			 m_pVerboseTooltip;

			//Another one. Will need to figure out the relation between class and proto.
			//static VectorAdapter<GameObjectClass*> protoList;

			SPHERE					bounding_sphere;
			cPrjID*					m_pCfg;
			ResourceInterfaceClass* m_pResourceInterfaceClass;
			long					m_objType;
			ST3D_Database*			m_logical_db;
			ST3D_Database*			m_visible_db;
		};

		bool isGameObjectClass( const types::GameObjectClass* const ptr );
			bool isCraftClass( const types::GameObjectClass* const ptr );
				bool isCargoShipClass( const types::GameObjectClass* const ptr );	
				bool isColonyClass( const types::GameObjectClass* const ptr );
				bool isFreighterClass( const types::GameObjectClass* const ptr );
				bool isMineArrayClass( const types::GameObjectClass* const ptr );
				bool isPlanetMiningBaseClass( const types::GameObjectClass* const ptr );
				bool isRepairShipClass( const types::GameObjectClass* const ptr );
				bool isResearchPodClass( const types::GameObjectClass* const ptr );
				bool isScavengerClass( const types::GameObjectClass* const ptr );
				bool isSensorArrayClass( const types::GameObjectClass* const ptr );
				bool isProducerClass( const types::GameObjectClass* const ptr );
					bool isConstructionRigClass( const types::GameObjectClass* const ptr );
					bool isEvolverClass( const types::GameObjectClass* const ptr );
					bool isPlanetClass( const types::GameObjectClass* const ptr );
					bool isResearchStationClass( const types::GameObjectClass* const ptr );
					bool isShipyardClass( const types::GameObjectClass* const ptr );
						bool isStarbaseClass( const types::GameObjectClass* const ptr );
					bool isMiningStationClass( const types::GameObjectClass* const ptr );
						bool isTradingStationClass( const types::GameObjectClass* const ptr );
			bool isTerrainObjectClass( const types::GameObjectClass* const ptr );
				bool isAreaEffectObjectClass( const types::GameObjectClass* const ptr );
					bool isBlackholeClass( const types::GameObjectClass* const ptr );
					bool isIonStormClass( const types::GameObjectClass* const ptr );
					bool isNebulaClass( const types::GameObjectClass* const ptr );
					bool isWormholeClass( const types::GameObjectClass* const ptr );
				bool isAsteroidFieldClass( const types::GameObjectClass* const ptr );
				bool isBackgroundObjectClass( const types::GameObjectClass* const ptr );
					bool isBackgroundPlanetClass( const types::GameObjectClass* const ptr );
				bool isLatinumNebulaClass( const types::GameObjectClass* const ptr );
				bool isScrapClass( const types::GameObjectClass* const ptr );
				bool isUtritiumBallClass( const types::GameObjectClass* const ptr );
			bool isConstructionObjectClass( const types::GameObjectClass* const ptr );
	}
}
