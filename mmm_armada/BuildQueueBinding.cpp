#include "BuildQueue.h"

namespace mmm
{
	void
	buildqueue_register( lua_State* state )
	{
		using namespace luabind;
		module(state)
		[
			class_<BuildQueue, BuildQueuePtr>( "BuildQueue" )
				.property( "empty", &BuildQueue::isEmpty )
				.property( "items", &BuildQueue::getItems )
				.property( "timeRemaining", &BuildQueue::getTimeRemaining )
				.def( "clear", &BuildQueue::clear )
				.def( "complete", &BuildQueue::complete )
				.def( "pop", &BuildQueue::pop )
				.def( "push", &BuildQueue::push )
				.def( "remove", &BuildQueue::remove )
		];
	}
}
