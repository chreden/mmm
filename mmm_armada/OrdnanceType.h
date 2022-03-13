#pragma once

#include "Type_Entity.h"

namespace mmm
{
	namespace types
	{
		//Move to file at some point.
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

			float	total;						//Done
			System	target;						
			float	threshold;					
			float	crewModifier;				
			float	hullCrewModifier;			
			Special	flags;						//Done
			float	specialValue;				
			int		m_whosReallyResponsible;	
		};

		struct WeaponClass;
		struct OrdnanceClass;
		struct Weapon;
		struct ST3D_Node;

		struct Ordnance
			: public Entity
		{
			char me[4];									//Crazy mentalists I don't know 
														//why they do this - this is a list
														//iterator
			WeaponClass*	 weaponClass;				//Next version
			OrdnanceClass*	 ordnanceClass;				//Next version (or quick fix)
			Weapon*			 ownerWeapon;				//Next version
			STDamage		 stDamage;					//Needs to be done
			int				 ownerHandle;				//Done
			int				 targetHandle;				//Done
			int				 reflectHandle;				
			Vector3			 targetLocationPos;			//Done
			const ST3D_Node* offensiveHardpoint;		
			const ST3D_Node* defensiveHardpoint;		
			Euler			 m_euler;					
			float			 m_lifetime;				//Done
			float			 m_dt;						
			bool			 m_reflected;				//Done
			int				 m_team_number;				//Done
		};
	}
}
