#include "Artillery.h"

namespace mmm
{
	void
	artillery_register( lua_State* state ) 
	{
		using namespace luabind;

		module(state)
		[
			class_<Artillery, Bullet, EntityPtr>( "Artillery" )
				.property("color", &Artillery::getArtilleryColor, &Artillery::setArtilleryColor )
		];
	}
}
