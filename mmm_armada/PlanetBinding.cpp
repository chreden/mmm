#include "Planet_Internal.h"
#include "Producer.h"
#include "Race_Internal.h"

namespace mmm
{
	void
	planet_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<Planet, Producer, EntityPtr>( "Planet" )
				.property( "colonyShip", &Planet::getColonyShip )
				.property( "hasShields", &Planet::getHasShields )
				.property( "maxPopulation", &Planet::getMaxPopulation )
				.property( "population", &Planet::getPopulation, &Planet::setPopulation )
				.property( "populationLevel", &Planet::getPopulationLevel )
				.property( "oldRace", &Planet::getOldRace )
				.scope
				[
					class_<eCivPopulationLevel>("PopulationLevel")
						.enum_("constants")
						[
							value("Unpopulated", UNPOPULATED_LEVEL),
							value("Sparse", SPARSE_LEVEL),
							value("Light", LIGHT_LEVEL),
							value("Medium", MEDIUM_LEVEL),
							value("Heavy", HEAVY_LEVEL)
						]
				]
		];
	}
}
