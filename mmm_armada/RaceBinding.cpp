#include "Race_Internal.h"

namespace mmm
{
	void 
	race_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<Race, RacePtr>( "Race" )
				.property( "boardingStrength", &Race::getBoardingStrength )	
				.property( "displayName", &Race::getDisplayName )
				.property( "name", &Race::getName )	
				.property( "repairStrength", &Race::getRepairStrength )
				.property( "number", &Race::getNumber )
				.scope
				[
					def( "find", (RacePtr (*)(int))&Race::find ),
					def( "find", (RacePtr (*)(const std::string&))&Race::find ),
					def( "getAll", &Race::getAll )
				]
		];
	}
}
