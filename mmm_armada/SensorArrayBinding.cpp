#include "SensorArray.h"

namespace mmm
{
	void
	sensorarray_register( lua_State* state )
	{
		using namespace luabind;
		module(state)
		[
			class_<SensorArray, Craft, EntityPtr>( "SensorArray" )
		];
	}
}
