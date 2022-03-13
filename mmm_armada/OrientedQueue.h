#pragma once

#include "SplineQueue.h"

namespace mmm
{
	namespace types { struct OrientedQueue; }

	class OrientedQueue
		: public SplineQueue
	{
	public:
		static OrientedQueuePtr create( types::OrientedQueue* queue );
		const Vector3 getEndOffset() const;
		const Vector3 getDirection() const;
	private:
		explicit OrientedQueue( types::OrientedQueue* queue );
		types::OrientedQueue* getOrientedQueue() const;
	};

	void orientedqueue_register( lua_State* state );
}
