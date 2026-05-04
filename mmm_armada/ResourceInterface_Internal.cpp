#include "ResourceInterface_Internal.h"
#include "Type_ResourceInterface.h"
#include "Type_GameObject.h"
#include "Type_Entity.h"
#include "Entity_Internal.h"

namespace mmm
{
    namespace
    {
        const std::size_t Address_GetResourceAmount = 0x004d64e0;
        const std::size_t Address_SetResourceAmount = 0x004d6500;

        class ResourceInterfaceCallback : public Container::Callback
        {
        public:
            explicit ResourceInterfaceCallback(ResourceInterface* iface)
                : interface_(iface)
            {
            }

            virtual ~ResourceInterfaceCallback()
            {
            }

            virtual float get(eResource resource) const
            {
                return interface_->getResourceAmount(resource);
            }

            virtual void set(eResource resource, float amount)
            {
                interface_->setResourceAmount(resource, amount);
            }
        private:
            ResourceInterface* interface_;
        };
    }

    ResourceInterface::ResourceInterface(types::GameObject* gameobject)
        : gameobject_(gameobject)
    {
    }

    bool ResourceInterface::getResourceIsInfinite() const
    {
        return getInterface()->m_isInfinite;
    }

    float ResourceInterface::getResourceAmount(eResource resource) const
    {
        return getInterface()->m_amtResource[resource];
    }

    Container ResourceInterface::getResources() const
    {
        return Container(std::shared_ptr<Container::Callback>(new ResourceInterfaceCallback(const_cast<ResourceInterface*>(this))));
    }

    std::shared_ptr<Entity> ResourceInterface::getOrbitalStation() const
    {
        return createEntityPtr(GetEntity<types::Entity>(getInterface()->m_orbitalID));
    }

    std::shared_ptr<Entity> ResourceInterface::getMiner() const
    {
        return createEntityPtr(GetEntity<types::Entity>(getInterface()->m_minerID));
    }

    int ResourceInterface::getLastTimeMined() const
    {
        return getInterface()->m_lastTimeMined;
    }

    void ResourceInterface::setResourceAmount(eResource resource, float amount)
    {
        getInterface()->m_amtResource[resource] = amount; 
    }

    void ResourceInterface::setResourceIsInfinite(bool value)
    {
        getInterface()->m_isInfinite = value;
    }

    bool ResourceInterface::isValid() const
    {
        return types::isResourceContainer(gameobject_);
    }

    types::ResourceInterface* ResourceInterface::getInterface() const
    {
        return gameobject_->m_pResourceInterface;
    }

    std::optional<int> ResourceInterface::index(lua_State* L, const std::string& key) const
    {
        if (key == "infinite")
        {
            lua_pushboolean(L, getResourceIsInfinite());
            return 1;
        }
        else if (key == "miner")
        {
            return entity_new(L, getMiner());
        }
        else if (key == "orbitalStation")
        {
            return entity_new(L, getOrbitalStation());
        }
        else if (key == "resources")
        {
            return container_new(L, getResources());
        }
        return std::nullopt;
    }

    std::optional<int> ResourceInterface::newindex(lua_State* L, const std::string& key)
    {
        if (key == "infinite")
        {
            setResourceIsInfinite(lua_toboolean(L, 3));
            return 0;
        }
        return std::nullopt;
    }
}
