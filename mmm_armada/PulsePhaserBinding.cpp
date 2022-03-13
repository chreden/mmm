#include "PulsePhaser_Internal.h"

namespace mmm
{
	void
	pulsephaser_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<PulsePhaser, Bullet, EntityPtr>( "PulsePhaser" )
				.property( "colour", &PulsePhaser::getPhaserColour, &PulsePhaser::setPhaserColour )
		];
	}
}
