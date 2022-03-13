#include "Explosion_Internal.h"

namespace mmm
{
	void
	explosion_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<Explosion, Entity, EntityPtr>( "Explosion" )
				.property( "entityResponsible", &Explosion::getEntityResponsible )
				.property( "radius", &Explosion::getRadius )
				.property( "soundPlayed", &Explosion::getSoundPlayed )
		];
	}
}
