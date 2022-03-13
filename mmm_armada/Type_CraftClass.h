#pragma once

#include "Type_GameObjectClass.h"
#include "Type_CraftSystem.h"

namespace mmm
{
	namespace types
	{
		struct CaptainsVoice;
		struct BorgMesh;
		struct PhysicsParameterSet;

		struct CraftClass 
			: public GameObjectClass
		{
			enum ePhysics
			{
				Physics_Smooth,
				Physics_Borg,
				Physics_Hovercraft
			};

			enum eSystem
			{
				ShieldGenerator,
				Engines,
				Weapon,
				LifeSupport,
				SystemCount
			};

			enum eShipClasses
			{
				Assault,
				Battleship,
				Cruiser,
				Destroyer,
				Frigate,
				Scout,
				Cargo,
				Colony,
				Construction,
				Mining,
				Repair,
				Special,
				Station,
				ClassCount
			};

			//Those mentalists. They are insane.
			//static const char * s_systemNames[0x0]
				

			float		tooCloseToTurn;
			float		pathLeadDistanceSquared;
			ePhysics	physics;
			float		shieldDelay;
			float		shieldRate;
			bool		m_disableShieldsOnTransport;
			bool		m_shipIsBuiltByShips;
			bool		m_shipIsBuiltByEvolution;
			bool		m_saneCrewLossMethod;
			float		healthRate;
			float		specialEnergyRate;
			float		crew;
			float		intrinsicValue;
			float		attackPower;
			bool		defaultGreenAlert;
			bool		isStation;
			bool		alwaysUseSpecialWeapons;
			bool		canAttack;
			bool		scout;
			bool		canAttackPlanets;
			bool		canOnlyAttackPlanets;
			float		footprintBuffer;
			float		m_eastBuffer;
			float		m_westBuffer;
			float		m_northBuffer;
			float		m_southBuffer;
			float		m_downBuffer;
			float		m_upBuffer;
			CraftSystem system[0x5];
			VectorAdapter<ST3D_Node*> targetHardpoints[0x5];
			VectorAdapter<ST3D_Node*> hullTargetHardpoints;
			VectorAdapter<ST3D_Node*> criticalTargetHardpoints;
			float		crewHitPercent;
			float		hullHitPercent;
			VectorAdapter<char*> hullTargetHardpointNames;
			VectorAdapter<char*> criticalTargetHardpointNames;
			cPrjID*		m_pSelfDestructClassID;
			cPrjID*		m_pFireballClassID;
			CaptainsVoice* m_captains_voice;
			bool		isHero;
			VectorAdapter<char*> craftNames;
			int*		craftNameFlags;
			float		m_boardingPartyStrength;
			float		m_percentNebulaWarn;
			bool		m_addToPlanner;
			float		m_combatSpeed;
			float		m_impulseSpeed;
			float		m_warpSpeed;
			float		m_lifeSupportLoss;
			float		m_rangeScan;
			float		m_damagedScan;
			float		m_shieldProtection;
			float		m_maxShields;
			ST3D_Node*  m_hull_damage_node;
			ST3D_Node*  m_shields_damage_node;
			ST3D_Node*  m_weapons_damage_node;
			ST3D_Node*  m_sensors_damage_node;
			ST3D_Node*  m_engines_damage_node;
			ST3D_Node*  m_lifesupport_damage_node;
			ST3D_Node*  m_borg_hierarchy_node;
			int			m_num_borg_meshes;
			BorgMesh*	m_borg_mesh_array;
			/*eShipTypeInfo*/ int m_type;
			eShipClasses m_shipClass;
			bool*		m_canHandleResource;
			bool		m_recyclesInPlace;
			int			m_maxExtraWeapons;
			WeaponClass* m_pMissileDetonator;
			PhysicsParameterSet** m_ppPhysParams;
			float		m_recrewRate;
		};
	}
}
