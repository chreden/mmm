#include "ProducerClass_Internal.h"
#include "CraftClass_Internal.h"

namespace mmm
{
	void
	producerclass_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<ProducerClass, CraftClass, GameObjectClassPtr>("ProducerClass")
				.def( "setitem", &ProducerClass::setitem ) //This is temporary.
		];
	}
}
