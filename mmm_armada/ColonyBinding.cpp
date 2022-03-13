#include "Colony_Internal.h"

namespace mmm
{
	void
	colony_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<Colony, Craft, EntityPtr>( "Colony" )
				.property( "planet", &Colony::getPlanet )
				.property( "colonists", &Colony::getColonists, &Colony::setColonists )
				.property( "initialColonists", &Colony::getInitialColonists, &Colony::setInitialColonists )
				.property( "initialPopulation", &Colony::getInitialPopulation, &Colony::setInitialPopulation )
		];
	}
}
