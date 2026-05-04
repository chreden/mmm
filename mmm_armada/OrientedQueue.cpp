#include "OrientedQueue.h"
#include "OrientedQueueType.h"

namespace mmm
{
    std::shared_ptr<OrientedQueue> OrientedQueue::create(types::OrientedQueue* queue)
    {
        return std::shared_ptr<OrientedQueue>(new OrientedQueue(queue));
    }

    OrientedQueue::OrientedQueue(types::OrientedQueue* queue)
        : SplineQueue(queue)
    {
    }

    types::OrientedQueue* OrientedQueue::getOrientedQueue() const
    {
        return static_cast<types::OrientedQueue*>(getQueue());
    }

    Vector3 OrientedQueue::getEndOffset() const
    {
        return getOrientedQueue()->m_endOffset;
    }

    Vector3 OrientedQueue::getDirection() const
    {
        return getOrientedQueue()->m_direction;
    }

    int OrientedQueue::index(lua_State* L, const std::string& key) const
    {
        if (key == "direction")
        {
            return vector_new(L, getDirection());
        }
        else if (key == "endOffset")
        {
            return vector_new(L, getEndOffset());
        }
        return SplineQueue::index(L, key);
    }
}
