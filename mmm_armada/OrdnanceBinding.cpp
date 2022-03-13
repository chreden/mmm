#include "Ordnance.h"
#include "Team_Internal.h"
#include "OrdnanceDamage.h"

namespace mmm
{
	void
	ordnance_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<Ordnance, Entity, EntityPtr>( "Ordnance" )
				.property( "damage", &Ordnance::getDamage )	
				.property( "lifetime", &Ordnance::getLifetime, &Ordnance::setLifetime )
				.property( "owner", &Ordnance::getOwner )
				.property( "ownerPlayer", &Ordnance::getTeam )	
				.property( "reflected", &Ordnance::getReflected )
				.property( "targetEntity", &Ordnance::getTarget, &Ordnance::setTarget )
				.property( "targetLocation", &Ordnance::getTargetLocation )
		];
	}
}
