#pragma once

#include "Type_Entity.h"

namespace mmm
{
    namespace types
    {
        struct STDamage
        {
            enum System
            {
                Engines = 0,
                LifeSupport,
                Weapons,
                Shield,
                Sensors,
                Crew,
                Hull,
                NumberOfSystems
            };

            float total;
            System target;
            float threshold;
            float crewModifier;
            float hullCrewModifier;
            Special flags;
            float specialValue;
            int m_whosReallyResponsible;
        };

        struct WeaponClass;
        struct OrdnanceClass;
        struct Weapon;
        struct ST3D_Node;

        struct Ordnance : public Entity
        {
            char me[4]; // List iterator
            WeaponClass* weaponClass;
            OrdnanceClass* ordnanceClass;
            Weapon* ownerWeapon;
            STDamage stDamage;
            int ownerHandle;
            int targetHandle;
            int reflectHandle;
            Vector3 targetLocationPos;
            const ST3D_Node* offensiveHardpoint;
            const ST3D_Node* defensiveHardpoint;
            Euler m_euler;
            float m_lifetime;
            float m_dt;
            bool m_reflected;
            int m_team_number;
        };
    }
}
