#include "OrientedQueue.h"
#include "OrientedQueueType.h"

namespace mmm
{
	OrientedQueuePtr
	OrientedQueue::create( types::OrientedQueue* queue )
	{
		return OrientedQueuePtr( new OrientedQueue( queue ) );
	}

	OrientedQueue::OrientedQueue( types::OrientedQueue* queue )
		: SplineQueue( queue )
	{

	}

	types::OrientedQueue*
	OrientedQueue::getOrientedQueue( ) const
	{
		return static_cast<types::OrientedQueue*>( getQueue() );
	}

	const Vector3 
	OrientedQueue::getEndOffset() const
	{
		return getOrientedQueue()->m_endOffset;
	}

	const Vector3 
	OrientedQueue::getDirection() const
	{
		return getOrientedQueue()->m_direction;
	}
}
