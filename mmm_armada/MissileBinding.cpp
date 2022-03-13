#include "Missile_Internal.h"

namespace mmm
{
	void
	missile_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<Missile, Ordnance, EntityPtr>( "Missile" )
				.property("omega", &Missile::getOmega, &Missile::setOmega )
				.property("seekTimer", &Missile::getSeekTimer )
				.property("turnLim2", &Missile::getTurnLim2, &Missile::setTurnLim2 )
		];
	}
}
