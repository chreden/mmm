#pragma once

#include "VectorAdapter.h"
#include "StringAdapter.h"
#include "MapAdapter.h"
#include "ListAdapter.h"

namespace mmm
{
    namespace types
    {
        struct DebriefingData
        {
            struct StarDate
            {
                float m_starDate;
            };

            struct DebriefingDataTeam
            {
                struct StrengthSnapshot
                {
                    uint32_t m_strength;
                    StarDate m_starDate;
                };

                struct PlayerStrength
                {
                    StrengthSnapshot m_data[1220];
                };

                struct PlanetInfo
                {
                    StringAdapter m_planetName;
                    int           m_team;
                    StarDate      m_stardate;
                };

                float m_dataUsed[21];
                VectorAdapter<void*> m_shipsDataList;
                VectorAdapter<void*> m_buildDataList;
                VectorAdapter<void*> m_tallyDataList;
                VectorAdapter<void*> m_battleDataList;
                PlayerStrength       m_playerStrength;
                ListAdapter<PlanetInfo> m_planetInfoList;
                VectorAdapter<void*> m_timelineBattleData;
                bool                 m_taken_over;
                bool                 m_quit;
                bool                 m_dropped;
                bool                 m_surrendered;
                bool                 m_winner;
                StringAdapter        m_name_taken_over_by;
                int                  m_teamColor;
                StringAdapter        m_name;
                StringAdapter        m_race;
                StringAdapter        m_actualRace;
                int                  m_global_id;
                bool                 m_human;
            };

            int                 m_curTime;
            float               m_curTimelineFreq;
            DebriefingDataTeam* m_team_data[9];
            int                 m_numPlayers;
            MapAdapter<int, VectorAdapter<void*>>* m_craftDataList;
        };

        static_assert(sizeof(DebriefingData::DebriefingDataTeam) == 10020);
        static_assert(sizeof(DebriefingData) == 52);

        DebriefingData* get_debriefing_data();
    }
}
