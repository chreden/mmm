#pragma once

#include "Queue.h"

namespace mmm
{
	namespace types { struct SplineQueue; }

	class SplineQueue
		: public Queue
	{
	public:
		explicit SplineQueue( types::SplineQueue* queue );
	private:
		types::SplineQueue* getSplineQueue() const;
	};

	void splinequeue_register( lua_State* state );
}
