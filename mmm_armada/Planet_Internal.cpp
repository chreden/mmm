#include "Planet_Internal.h"
#include "Type_Planet.h"
#include "Race_Internal.h"
#include "LuaBinding.h"

namespace mmm
{
    namespace
    {
        const std::size_t Address_GetMaxPopulation	=	0x004b5550;
        const std::size_t Address_GetPopulation		=	0x004b5960;
        const std::size_t Address_SetPopulation		=	0x004b5970;
    }

    PlanetPtr Planet::create(types::Entity* entity)
    {
        return PlanetPtr(new Planet(static_cast<types::Planet*>(entity)));
    }

    Planet::Planet(types::Planet* planet)
        : Producer(planet)
    {

    }

    std::shared_ptr<Entity> Planet::getColonyShip() const
    {
        return createEntityPtr(GetEntity<types::Entity>(getPlanet()->m_colonyShip));
    }

    float Planet::getMaxPopulation() const
    {
        typedef float (types::Planet::*MemFunction)() const;
        MemFunction function = memory_function< MemFunction >(Address_GetMaxPopulation);
        return (getPlanet()->*function)();
    }

    float Planet::getPopulation() const
    {
        typedef float (types::Planet::*MemFunction) () const;
        MemFunction function = memory_function< MemFunction >(Address_GetPopulation);
        return (getPlanet()->*function)();
    }

    void Planet::setPopulation(float value)
    {
        typedef void (types::Planet::*MemFunction) (float);
        MemFunction function = memory_function< MemFunction >(Address_SetPopulation);
        (getPlanet()->*function)(value);
    }

    bool Planet::getHasShields() const
    {
        return getPlanet()->m_builtShields;
    }

    eCivPopulationLevel Planet::getPopulationLevel() const
    {
        return getPlanet()->m_populationLevel;
    }

    std::shared_ptr<Race> Planet::getOldRace() const
    {
        return Race::create(getPlanet()->m_pOldRace);
    }

    types::Planet* Planet::getPlanet() const
    {
        return static_cast<types::Planet*>(getEntity());
    }

    int Planet::index(lua_State* L, const std::string& key) const
    {
        if (key == "colonyShip")
        {
            return entity_new(L, getColonyShip());
        }
        else if (key == "hasShields")
        {
            lua_pushboolean(L, getHasShields());
            return 1;
        }
        else if (key == "maxPopulation")
        {
            lua_pushnumber(L, getMaxPopulation());
            return 1;
        }
        else if (key == "population")
        {
            lua_pushnumber(L, getPopulation());
            return 1;
        }
        else if (key == "populationLevel")
        {
            lua_pushnumber(L, getPopulationLevel());
            return 1;
        }
        else if (key == "oldRace")
        {
            return race_new(L, getOldRace());
        }
        return Producer::index(L, key);
    }

    int Planet::newindex(lua_State* L, const std::string& key)
    {
        if (key == "population")
        {
            setPopulation(lua_tonumber(L, 3));
            return 0;
        }
        return Producer::newindex(L, key);
    }

    void planet_register(lua_State* L)
    {
        lua_newtable(L);
        create_enum(L, "PopulationLevel",
            {
                { "Unpopulated", UNPOPULATED_LEVEL },
                { "Sparse", SPARSE_LEVEL },
                { "Light", LIGHT_LEVEL },
                { "Medium", MEDIUM_LEVEL },
                { "Heavy", HEAVY_LEVEL }
            });
        lua_setglobal(L, "Planet");
    }
}
