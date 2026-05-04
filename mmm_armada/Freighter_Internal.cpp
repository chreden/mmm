#include "Freighter_Internal.h"
#include "Type_Freighter.h"

namespace mmm
{
    namespace
    {
        const std::size_t Address_GetResourceSpaceRemaining	= 0x004b1800;

        int freighter_get_max_amount(lua_State* L)
        {
            const auto self = get_entity<Freighter>(L, 1);
            lua_pushnumber(L, self->getMaxAmount(static_cast<eResource>(lua_tonumber(L, 2))));
            return 1;
        }
    }

    std::shared_ptr<Freighter> Freighter::create(types::Entity* entity)
    {
        return std::shared_ptr<Freighter>(new Freighter(static_cast<types::Freighter*>(entity)));
    }

    Freighter::Freighter(types::Freighter* freighter)
        : Craft(freighter)
    {
    }

    types::Freighter* Freighter::getFreighter() const
    {
        return static_cast<types::Freighter*>(getEntity());
    }

    eResource Freighter::getResourceCarried() const
    {
        return getFreighter()->m_currentlyHolding;
    }

    float Freighter::getSpaceRemaining() const
    {
        typedef float (types::Freighter::*MemFunction)(eResource) const;
        MemFunction function = memory_function<MemFunction>(Address_GetResourceSpaceRemaining);
        return (getFreighter()->*function)(getResourceCarried());
    }

    float Freighter::getAmountCarried() const
    {
        return getFreighter()->m_resourceHeld;
    }

    float Freighter::getMaxAmount(eResource resource) const
    {
        if (resource < 0 || resource > NUMBER_OF_RESOURCES)
        {
            return 0;
        }
        return getFreighter()->m_maxResource[resource];
    }

    float Freighter::getMaxAmountCurrent() const
    {
        return getFreighter()->m_maxResource[getResourceCarried()];
    }

    bool Freighter::getDroppingOff() const
    {
        return getFreighter()->m_droppingOff;
    }

    std::shared_ptr<Entity> Freighter::getResourceSource() const
    {
        return createEntityPtr(GetEntity<types::Entity>(getFreighter()->m_resourceHandle));
    }

    std::shared_ptr<Entity> Freighter::getStation() const
    {
        return createEntityPtr(GetEntity<types::Entity>(getFreighter()->m_station));
    }

    void Freighter::setResourceCarried(eResource resource)
    {
        getFreighter()->m_currentlyHolding = resource;
    }

    void Freighter::setAmountCarried(float value)
    {
        getFreighter()->m_resourceHeld = value;
    }

    int Freighter::index(lua_State* L, const std::string& key) const
    {
        if (key == "amount")
        {
            lua_pushnumber(L, getAmountCarried());
            return 1;
        }
        else if (key == "getMaxAmount")
        {
            lua_pushcfunction(L, freighter_get_max_amount);
            return 1;
        }
        else if (key == "resource")
        {
            lua_pushnumber(L, getResourceCarried());
            return 1;
        }
        else if (key == "spaceRemaining")
        {
            lua_pushnumber(L, getSpaceRemaining());
            return 1;
        }
        else if (key == "droppingOff")
        {
            lua_pushboolean(L, getDroppingOff());
            return 1;
        }
        else if (key == "maxAmount")
        {
            lua_pushnumber(L, getMaxAmountCurrent());
            return 1;
        }
        else if (key == "source")
        {
            return entity_new(L, getResourceSource());
        }
        else if (key == "station")
        {
            return entity_new(L, getStation());
        }
        return Craft::index(L, key);
    }

    int Freighter::newindex(lua_State* L, const std::string& key)
    {
        if (key == "amount")
        {
            setAmountCarried(lua_tonumber(L, 3));
            return 0;
        }
        else if (key == "resource")
        {
            setResourceCarried(static_cast<eResource>(lua_tonumber(L, 3)));
            return 0;
        }
        return Craft::newindex(L, key);
    }
}