#pragma once

namespace mmm
{
	namespace types
	{
		class AIP;

		class SpecialWeaponUtility
		{
			char _padding[0x22];
		};

		class Goal;

		struct Scheduler
		{
			char _padding_[0x9C];
		};

		class Strategic_Map
		{

		};

		class AI_Base_Building;

		struct AI_Team
		{
			virtual ~AI_Team();
			int m_teamID;
			unsigned char m_AI_controlled;
			unsigned char m_enabled;
			unsigned char m_useWormholes;
			unsigned char m_friendTransport;
			unsigned char m_enemyTransport;
			unsigned char m_multipleFire;
			float m_distressCallDistance;
			unsigned char m_goalsRecomputed;
			float m_specialWeaponTimer;
			SpecialWeaponUtility utilityInfo;
			AIP* m_AIP;
			Scheduler m_scheduler;
			Strategic_Map* m_map;
			AI_Base_Building* m_base;
			unsigned char m_forceStrategyRecompute;
			float m_weaponTimerModifier;
			float m_unmodifiedWeaponTimerMax;
			unsigned long m_resourcePriorities[0x6];
			int m_resourceBaseCount[0x6];
		};

		class AIP_Manager;

		enum Team_Strength
		{

		};

		struct AI
		{
			virtual			~AI();
			AI_Team*		m_team;
			int				map_rows;
			int				map_columns;
			int				gridside;
			hot_int*		m_resources_team[0x9];
			int				m_allied_resources[0x9];
			int				m_total_resources;
			hot_float*		m_strength_team[0x9];
			float			m_allied_strength[0x9];
			float			m_total_strength;
			int				m_calc_statistics_counter;
			int				m_AIDebuggingLevel;
			int				m_debugTeam;
			AIP_Manager*	m_API_manager;
			int				m_num_teams;
			Team_Strength	m_team_strength;
			float*			m_baselineStrength;
			unsigned char*	m_actingTough;
			float*			m_attackAllTime;
			unsigned char*	m_kamikazeDone;
			float*			m_peakActingToughStrength;
			int				m_strategy_ctyle;
		};
	}
}

