#include "SplineQueue.h"
#include "SplineQueueType.h"

namespace mmm
{
	SplineQueue::SplineQueue( types::SplineQueue* queue )
		: Queue( queue )
	{

	}

	types::SplineQueue*
	SplineQueue::getSplineQueue() const
	{
		return static_cast<types::SplineQueue*>( getQueue() );
	}
}