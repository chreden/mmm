#include "Colony_Internal.h"
#include "Type_Colony.h"
#include "ColonyClass_Internal.h"
#include "Type_ColonyClass.h"

namespace mmm
{
    std::shared_ptr<Colony> Colony::create(types::Entity* entity)
    {
        return std::shared_ptr<Colony>(new Colony(static_cast<types::Colony*>(entity)));
    }

    Colony::Colony(types::Colony* colony)
        : Craft(colony)
    {
    }

    types::Colony* Colony::getColony() const
    {
        return static_cast<types::Colony*>(getEntity());
    }

    std::shared_ptr<Entity> Colony::getPlanet() const
    {
        return createEntityPtr(GetEntity<types::Entity>(getColony()->m_planetHandle));
    }

    int Colony::getColonists() const
    {
        return getColony()->m_colonists;
    }

    int Colony::getInitialColonists() const
    {
        return getColony()->m_initialColonists;
    }

    float Colony::getInitialPopulation() const
    {
        return getColony()->m_initialPopulation;
    }

    void Colony::setColonists(int value)
    {
        getColony()->m_colonists = value;
    }

    void Colony::setInitialColonists(int value)
    {
        getColony()->m_initialColonists = value;
    }

    void Colony::setInitialPopulation(float value)
    {
        getColony()->m_initialPopulation = value;
    }

    int Colony::index(lua_State* L, const std::string& key) const
    {
        if (key == "colonists")
        {
            lua_pushnumber(L, getColonists());
            return 1;
        }
        else if (key == "initialColonists")
        {
            lua_pushnumber(L, getInitialColonists());
            return 1;
        }
        else if (key == "initialPopulation")
        {
            lua_pushnumber(L, getInitialPopulation());
            return 1;
        }
        else if (key == "planet")
        {
            return entity_new(L, getPlanet());
        }
        return 0;
    }

    int Colony::newindex(lua_State* L, const std::string& key)
    {
        if (key == "colonists")
        {
            setColonists(lua_tonumber(L, 3));
            return 0;
        }
        else if (key == "initialColonists")
        {
            setInitialColonists(lua_tonumber(L, 3));
            return 0;
        }
        else if (key == "initialPopulation")
        {
            setInitialPopulation(lua_tonumber(L, 3));
            return 0;
        }
        return 0;
    }
}
