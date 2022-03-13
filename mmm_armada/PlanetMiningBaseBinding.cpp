#include "PlanetMiningBase.h"

namespace mmm
{
	void
	planetminingbase_register( lua_State* state )
	{
		using namespace luabind;
		module(state)
		[
			class_<PlanetMiningBase, Craft, EntityPtr>("PlanetMiningBase")
				.property( "planet", &PlanetMiningBase::getPlanet, &PlanetMiningBase::setPlanet )
				.property( "orbitalOmega", &PlanetMiningBase::getOrbitOmega, &PlanetMiningBase::setOrbitOmega )
				.property( "numberOfHoldingBeams", &PlanetMiningBase::getNumHoldingBeams, &PlanetMiningBase::setNumHoldingBeams )
		];
	}
}