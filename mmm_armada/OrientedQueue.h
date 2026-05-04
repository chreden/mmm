#pragma once

#include "SplineQueue.h"

namespace mmm
{
    namespace types { struct OrientedQueue; }

    class OrientedQueue
        : public SplineQueue
    {
    public:
        static std::shared_ptr<OrientedQueue> create(types::OrientedQueue* queue);
        Vector3 getEndOffset() const;
        Vector3 getDirection() const;
        int index(lua_State* L, const std::string& key) const override;
    private:
        explicit OrientedQueue(types::OrientedQueue* queue);
        types::OrientedQueue* getOrientedQueue() const;
    };
}
