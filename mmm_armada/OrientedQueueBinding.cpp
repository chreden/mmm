#include "OrientedQueue.h"

namespace mmm
{
	void
	orientedqueue_register( lua_State* state )
	{
		using namespace luabind;
		module(state)
		[
			class_<OrientedQueue, SplineQueue, QueuePtr>( "OrientedQueue" )
				.property( "direction", &OrientedQueue::getDirection )	
				.property( "endOffset", &OrientedQueue::getEndOffset )
		];
	}
}
