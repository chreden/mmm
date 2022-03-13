#include "UtritiumBall_Internal.h"

namespace mmm
{
	void
	utritiumball_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<UtritiumBall, TerrainObject, EntityPtr>( "UtritiumBall" )
				.property( "timeLeft", &UtritiumBall::getTimeLeft, &UtritiumBall::setTimeLeft )
				.property( "owner", &UtritiumBall::getOwner )
		];
	}
}
