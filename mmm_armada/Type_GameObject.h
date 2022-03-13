#pragma once

#include "Type_Entity.h"

namespace mmm
{
	namespace types
	{
		struct ResourceInterface;
		struct GameObjectClass;
		struct Race;

		struct GameObject : public Entity
		{
			virtual ~GameObject( ) = 0;

			static std::list<GameObject*>* objectList;
			static void* objectRange;

			//EffectList Effects; //specialobjecteffect*
			//This should be an efect list but cant get the size right,
			//so just going to pad with chars for now
			char effects[12];

			int m_numParticleEffects;
			void* m_billboard_effect; //st3d_spritenodedata
			GameObjectClass* m_class; //const gameobjectclass* 
			void* aiProcess; //AiProcess*
			char* label;
			AiCmdInfo curCmd;
			AiCmdInfo nextCmd;
			Vector3 m_position;
			Euler m_euler;
			float collisionRadius;
			int teamNumber;
			void* teamList;
			int perceivedTeam;
			void* teamEffect;//TIMEDCHANGETEAM
			Race* m_pRace; //race*
			unsigned long invalidAsTarget;
			unsigned long ignoredAsTarget;
			void* m_cloakDevice; //CloakingDevice*
			bool m_avoidMe;
			bool m_invincible;
			bool isSelected;
			bool isPhaseCloaked;
			bool reflectMissile;
			bool reflectBeam;
			bool isHiddenBySpecial;
			bool m_is_destroyed;
			float m_reflectMissileRatio;
			float m_reflectBeamRatio;
			float m_reflectHitOwnerRatio;
			int m_groupNumber;
			void* scanner;
			void* carrier;
			void* m_pWeaponButtonList;
			void* m_pBuildButtonList;
			int who_shot_me;
			int who_i_shot;
			int last_enemy_to_hit_me;
			int team_that_shot_me;
			float when_last_hit_by_enemy;
			float when_i_shot;
			float m_whenLastBattleLogged;
			void* hitOrdClass;
			int m_enemyOfAllUnlike;
			float m_healthRatio;
			float m_curHealth;
			float m_maxHealth;
			float m_specialEnergyRatio;
			float m_maxSpecialEnergy;
			float m_curSpecialEnergy;
			void* specialFlag;
			void* m_holoEffect;
			void* m_tractorOrdnance;
			ResourceInterface* m_pResourceInterface;	//Save this stuff!
			bool m_force_onto_map;
			bool m_goneRabid;
			bool m_cannotDie;
			bool m_cameraDistanceCulled;
				
			//CraftIter me; Should be a craft iterator, but cant
			//get the size right
			char me[ 4 ];
		};
	}
}