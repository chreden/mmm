#include "Team_Internal.h"
#include "Race_Internal.h"

namespace mmm
{
	void
	team_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<Team, TeamPtr>( "Player" )
				.def( constructor<int>() )
				.property( "color", &Team::getColor, &Team::setColor )
				.property( "isAI", &Team::getIsAI, &Team::setIsAI )
				.property( "maxCrew", &Team::getMaxCrew, &Team::setMaxCrew )
				.property( "maxOfficers", &Team::getMaxOfficers, &Team::setMaxOfficers )
				.property( "name", &Team::getName, &Team::setName )
				.property( "number", &Team::getNumber )
				.property( "race", &Team::getRace, &Team::setRace )
				.scope
				[
					class_<Team::Resources, Team::ResourcesPtr>( "Resources" )
						.property("dilithium", &Team::Resources::getDilithium, &Team::Resources::setDilithium )
						.property("metal", &Team::Resources::getMetal, &Team::Resources::setMetal )
						.property("latinum", &Team::Resources::getLatinum, &Team::Resources::setLatinum )
						.property("biomatter", &Team::Resources::getBiomatter, &Team::Resources::setBiomatter )
						.property("crew", &Team::Resources::getCrew, &Team::Resources::setCrew )
                        .property("tritanium", &Team::Resources::getLatinum, &Team::Resources::setLatinum )
                        .property("collectiveConnections", &Team::Resources::getMetal, &Team::Resources::setMetal )
                        .property("supply", &Team::Resources::getBiomatter, &Team::Resources::setBiomatter ),
					class_<eSlotType>("SlotType")
						.enum_("constants")
						[
							value("None", ST_None),
							value("Human", ST_Human),
							value("Observer", ST_Observer),
							value("AI_Easy", ST_AI_Easy),
							value("AI_Normal", ST_AI_Normal),
							value("AI_Hard", ST_AI_Hard ),
							value("AI_Neural", ST_AI_Neural)
						],
					class_<eTeamRelation>("Relation")
						.enum_("constants")
						[
							value("Enemy", TEAM_ENEMY),
							value("Neutral", TEAM_NEUTRAL),
							value("Ally", TEAM_ALLY)
						],
					class_<eTradeDirection>("TradeDirection")
						.enum_("constants")
						[
							value("To", TradeDir_To),
							value("From", TradeDir_From)
						]
				]
				.property( "resources", &Team::getResources )
				.property( "slotType", &Team::getSlotType )
				.property("useWormholes", &Team::getUseWormholes, &Team::setUseWormholes)
				.def( "getAmountTraded", &Team::getAmountTraded )
				.def( "getRelation", &Team::getRelation )
				.def( "loadAIP", &Team::loadAIP )
				.def( "setRelation", &Team::setRelation )
		];
	}
}
