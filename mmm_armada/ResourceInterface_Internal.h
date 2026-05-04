#pragma once

#include <optional>

#include "Container.h"

namespace mmm
{
    namespace types
    {
        struct ResourceInterface;
        struct GameObject;
    }

    class Entity;
    class GameObject;

    class ResourceInterface
    {
    public:
        explicit ResourceInterface(types::GameObject* gameobject);
        virtual ~ResourceInterface() = default;

        bool getResourceIsInfinite() const;
        float getResourceAmount(eResource resoruce) const;
        std::shared_ptr<Entity> getOrbitalStation() const;
        std::shared_ptr<Entity> getMiner() const;
        int getLastTimeMined() const;
        Container getResources() const;
        void setResourceAmount(eResource resource, float amount);
        void setResourceIsInfinite(bool value);
        bool isValid() const;

        std::optional<int> index(lua_State* L, const std::string& key) const;
        std::optional<int> newindex(lua_State* L, const std::string& key);
    private:
        types::ResourceInterface* getInterface() const;
        types::GameObject* gameobject_;
    };
}