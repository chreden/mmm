#include "EvolverClass_Internal.h"

namespace mmm
{
	void
	evolverclass_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<EvolverClass, ProducerClass, GameObjectClassPtr>( "EvolverClass" )
		];
	}
}
