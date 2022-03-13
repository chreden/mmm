#include "MiningStationClass_Internal.h"

namespace mmm
{
	void
	miningstationclass_register( lua_State* state )
	{
		using namespace luabind;
		module(state)
		[
			class_<MiningStationClass, ProducerClass, GameObjectClassPtr>( "MiningStationClass" )
		];
	}
}
