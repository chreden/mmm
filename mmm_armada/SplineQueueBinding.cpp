#include "SplineQueue.h"

namespace mmm
{
	void
	splinequeue_register( lua_State* state )
	{
		using namespace luabind;
		module(state)
		[
			class_<SplineQueue, Queue, QueuePtr>( "SplineQueue" )
		];
	}
}
