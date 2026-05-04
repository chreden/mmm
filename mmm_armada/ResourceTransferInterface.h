#pragma once

#include <memory>

#include "Container.h"

namespace mmm
{
    namespace types
    {
        struct ResourceTransferInterface;
        struct GameObject;
    }

    class Entity;
    class OrientedQueue;
    class ResourceTransferInterface
    {
    public:
        explicit  ResourceTransferInterface(types::GameObject* object);
        virtual   ~ResourceTransferInterface() { };
        bool  isShipDocked() const;
        std::shared_ptr<Entity> getDockedShip() const;
        Container getResourceRates() const;
        std::shared_ptr<OrientedQueue> getMiningQueue() const;
        float getResourceRate(eResource res) const;
        void setResourceRate(eResource res, float value);
        int index(lua_State* L, const std::string& key) const;
    private:
        types::ResourceTransferInterface* getResourceTransferInterface() const;
        types::GameObject* object_;
    };

    void resourcetransferinterface_register(lua_State* state);
}
