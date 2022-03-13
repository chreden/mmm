#include "AsteroidField.h"

namespace mmm
{
	void 
	asteroidfield_register( lua_State* state )
	{
		using namespace luabind;
		module(state)
		[
			class_<AsteroidField, TerrainObject, EntityPtr>( "AsteroidField" )
		];
	}
}
