#include "Phaser_Internal.h"

namespace mmm
{
	void
	phaser_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<Phaser, Beam, EntityPtr>( "Phaser" )
				.property( "color", &Phaser::getPhaserColour, &Phaser::setPhaserColour )
		];
	}
}
