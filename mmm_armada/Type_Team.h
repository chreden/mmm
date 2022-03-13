#pragma once

#include "VectorAdapter.h"
#include "StringAdapter.h"

namespace mmm
{
	namespace types
	{
		enum eSlotType
		{
			ST_NONE = 0,
			ST_HUMAN,
			ST_COMPUTER_EASY,
			ST_COMPUTER_MEDIUM,
			ST_COMPUTER_HARD,
			ST_COMPUTER_NEURAL
		};

		struct GameSetupSlotDetails
		{
			char		_padding_[0x30];
			eSlotType	m_slot_type;
			char		_endpadding[14];
		};

		struct GameSetupDetails
		{
			char				 _padding_[ 0xF4 ];
			GameSetupSlotDetails m_slot_details[0x8];
		};

		struct GameSetup
		{
		public:
				

			int m_local_slot;
			int m_host_slot;
			int m_revision;
			class Transport * m_transport;
			class GameSetupDetails * m_game_setup_details;
		};
	
		struct Race;

		class Team
		{
		public:
			static char		s_teamMessage[ 500 ];
			static Team*	s_pTeamList[ 9 ];
			static bool	s_showTradesToTeam;
				
			int				m_teamColorIndex;
			int				m_mapColorIndex;
			ST3D_Colour		m_teamColor;
			ST3D_Colour		m_mapColor;
			int				m_numUnits;
			unsigned long	m_visible_teams;
			float			m_dilithium;
			float			m_dilithiumSent[ 9 ];
			float			m_dilithiumReceieved[ 9 ];
			float			m_latinum;
			float			m_latinumSent[ 9 ];
			float			m_latinumRecieved[ 9 ];
			float			m_metal;
			float			m_metalSent[ 9 ];
			float			m_metalRecieved[ 9 ];
			float			m_crew;
			float			m_currentCrewCapacity;
			float			m_startingCrewCapacity;
			float			m_crewSent[ 9 ];
			float			m_crewReceived[ 9 ];
			float			m_officers;
			int				m_max_officers;
			float			m_biomatter;
			int				m_teamNumber;
			eTeamRelation	m_relationship[ 9 ];
			int				m_orderedAllyShipAttacks[ 9 ];
			int				m_orderedAllyStationAttacks[ 9 ];
			float			m_timeOfLastAllyAttack[ 9 ];
			void*			m_shipUpgradeCount[ 2 ];	//Team::UpgradeInfo*
			float			m_shieldAbsorptionModifier;
			float			m_shieldHitpointModifier;
			float			m_weaponDamageModifier;
			float			m_weaponDelayModifier;
			float			m_impulseEngineModifier;
			float			m_warpEngineModifier;

			static int		s_cfgMAX_CREW;
			static int		s_cfgMAX_DILITHIUM;
			static int		s_cfgMAX_LATINUM;
			static int		s_cfgMAX_METAL;
			static int		s_cfgMAX_BIOMATTER;
			static int		s_cfgMAX_OFFICERS;
			static int		s_cfgSTARTING_CREW;
			static int		s_cfgSTARTING_CREW_CAP;
			static int		s_cfgSTARTING_DILITHIUM;
			static int		s_cfgSTARTING_LATINUM;
			static int		s_cfgSTARTING_METAL;
			static int		s_cfgDEFAULT_OFFICER_LIMIT;

			int				m_numberFerengiKilled;

			static int		giveViewRef[9][9];
			VectorAdapterString m_names;
			StringAdapter		m_name_string;
			Race*			m_race;
			eSlotType		m_team_type; //eSlotType
			bool			m_is_ai;
			unsigned char	m_started;
			const unsigned char	m_infinite_resources;
		};	
	}
}