#include "Queue.h"

namespace mmm
{
	void
	queue_register( lua_State* state )
	{
		using namespace luabind;
		module(state)
		[
			class_<Queue, QueuePtr>("Queue")
				.property( "size", &Queue::getSize )
				.property( "entries", &Queue::getEntries )
				.property( "offset", &Queue::getOffset )
		];
	}
}
