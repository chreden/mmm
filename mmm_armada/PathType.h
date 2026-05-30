#pragma once

namespace mmm
{
    namespace types
    {
        struct AiPath
        {
            int pointCount;
            Vector3* points;
            int pathType; 
            float asteroid_belt_speed;
            int m_nebula_type;
            int me;
            bool m_pathPlanningInited;
            char* m_pLabel;
            char* m_pDistances;
        };
    }
}
