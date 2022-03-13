#pragma once

#include "Type_Producer.h"

namespace mmm
{
	namespace types
	{
		struct Race;

		struct Planet : public Producer
		{
			float				m_civilianPopulation;			//Done
			eCivPopulationLevel m_populationLevel;				//Done
			void*				m_pPlanetDatabase;				//Ignore
			int					m_colonyShip;					//Done
			float				m_civilianPopulationModifier;	//Not done
			void*				m_pBattleInfo;					//Ignore
			Race*				m_pOldRace;						//Done
			float				m_oldCivilianPopulation;		//Ignore
			bool				m_builtShields;					//Done
		};
	}
}
