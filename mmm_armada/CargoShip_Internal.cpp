#include "CargoShip_Internal.h"
#include "Type_CargoShip.h"

namespace mmm
{
    CargoShipPtr CargoShip::create(types::Entity* entity)
    {
        return CargoShipPtr(new CargoShip(static_cast<types::CargoShip*>(entity)));
    }

    CargoShip::CargoShip(types::CargoShip* cargoShip)
        : Craft(cargoShip)
    {
    }

    types::CargoShip* CargoShip::getCargoShip() const
    {
        return static_cast<types::CargoShip*>(getEntity());
    }

    std::shared_ptr<Entity> CargoShip::getStartStation() const
    {
        return createEntityPtr(GetEntity<types::Entity>(getCargoShip()->m_startStation));
    }

    std::shared_ptr<Entity> CargoShip::getDestinationStation() const
    {
        return createEntityPtr(GetEntity<types::Entity>(getCargoShip()->m_goalStation));
    }

    bool CargoShip::getIsTrading() const
    {
        return getCargoShip()->m_isTrading;
    }

    float CargoShip::getMaxCargo() const
    {
        return getCargoShip()->m_maxCargo;
    }

    eResource CargoShip::getNextResource() const
    {
        return getCargoShip()->m_nextCargoType;
    }

    float CargoShip::getCargoAmount() const
    {
        if(getCargoShip()->m_pGoods)
        {
            return getCargoShip()->m_pGoods->m_amtGoods;
        }
        return 0.0f;
    }

    eResource CargoShip::getResource() const
    {
        if(getCargoShip()->m_pGoods)
        {
            return getCargoShip()->m_pGoods->m_resource;
        }
        return RESOURCE_CREW;
    }

    std::string CargoShip::getCargoName() const
    {
        if(getCargoShip()->m_pGoods)
        {
            return getCargoShip()->m_pGoods->m_pCargoDesc->key;
        }
        return std::string();
    }

    bool CargoShip::getIsFull() const
    {
        if(getCargoShip()->m_pGoods)
        {
            return getCargoShip()->m_pGoods->m_full;
        }
        return false;
    }

    int CargoShip::index(lua_State* L, const std::string& key) const
    {
        if (key == "cargoAmount")
        {
            lua_pushnumber(L, getCargoAmount());
            return 1;
        }
        else if (key == "cargoName")
        {
            lua_pushstring(L, getCargoName().c_str());
            return 1;
        }
        else if (key == "currentCargo")
        {
            lua_pushnumber(L, getResource());
            return 1;
        }
        else if (key == "destinationStation")
        {
            return entity_new(L, getDestinationStation());
        }
        else if (key == "full")
        {
            lua_pushboolean(L, getIsFull());
            return 1;
        }
        else if (key == "maxCargo")
        {
            lua_pushnumber(L, getMaxCargo());
            return 1;
        }
        else if (key == "nextCargo")
        {
            lua_pushnumber(L, getNextResource());
            return 1;
        }
        else if (key == "startStation")
        {
            return entity_new(L, getStartStation());
        }
        else if (key == "trading")
        {
            lua_pushboolean(L, getIsTrading());
            return 1;
        }
        return 0;
    }
}