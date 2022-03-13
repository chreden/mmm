#pragma once

#include "StringAdapter.h"

namespace mmm
{
	namespace types
	{
		class CityAllocArray;

		struct Race
		{
		public:
			//static int s_numberOfRaces;						//Done
			//static class Race** s_ppRaces;					//Done
			//static class Race* s_missionRace;
			//static class Race::RaceStatic* s;
			//static int s_raceCounter;
			//static int s_numInstantActionSlots;

			virtual ~Race() = 0;
			float repairYellow;
			float repairRed;
			float weaponYellow;
			float weaponRed;
			char m_name[0x40];									//Done
			char m_displayKey[0x40];							//Done
			char m_officerName[0x40];
			char m_officerRes[0x40];
			char m_officerTooltip[0x40];
			char m_officerVerboseTooltip[0x40];
			char m_configurationFilename[0x40];
			char m_spriteFilename[0x40];
			char m_singlePlayerMusic[0x20];						//Done (used in Media)
			char m_multiPlayerMusic[0x20];
			char m_transportSprite[0x20];
			float m_maxOfficerMultiplier;
			float repairStrength;								//Done
			float boardingStrength;								//Done
			float retreatStrength;
			float crewRetreatRatio;
			float crewYellowThreshold;
			float crewRedThreshold;
			float crewAccumulationRate;
			float planetCrewAccumulationModifier;
			StringAdapter startingUnitsName[0x9][0x3];
			int m_raceNumber;									//Done
			long m_instantActionSlot;
			unsigned char m_transportToFriendsOnNotEasy;
			unsigned char m_transportToEnemyOnHard;
			char m_cityTextureName[0x8];
			char m_atmosphereTextureName[0x8];
			ST3D_Colour m_atmosphereTint;
			float m_numCities;
			ST3D_Colour m_color;
			float m_recycleDilithiumFraction;
			float m_recycleMetalFraction;
			float m_miningModifier;
			unsigned char m_canPlayCollectLatinum;
			unsigned char m_canPlayColonizePlanets;
			unsigned char m_canPlayCaptureTheFlag;
			unsigned char m_canCommandeer;
			unsigned char m_canBeCommandeered;
			unsigned char m_canTrade;
			unsigned char m_affectedByPsionicInsanity;
			char m_rolloverSound[0x40];
			char m_clickSound[0x40];
			const CityAllocArray * m_cityAllocArray[0x2];
			char m_creationLabel[0x20];
			char m_recycledLabel[0x20];
			char m_officerEventName[0x80];
			int m_startingResources[0x6][0x2];
		};
	}
}
