#include "PlanetMiningBase.h"
#include "PlanetMiningBaseType.h"
#include "Type_Planet.h"

namespace mmm
{
    namespace
    {
        const std::size_t Function_SetPlanet = 0x004b7250;

        void PlanetMiningBase_SetPlanet(types::PlanetMiningBase* base,
                                         types::Planet* planet)
        {
            (base->*memory_function<void (types::PlanetMiningBase::*)(types::Planet*)>(Function_SetPlanet))
                    (planet);
        }
    }

    PlanetMiningBasePtr PlanetMiningBase::create(types::Entity* ent)
    {
        return PlanetMiningBasePtr(new PlanetMiningBase(static_cast<types::PlanetMiningBase*>(ent)));
    }

    PlanetMiningBase::PlanetMiningBase(types::PlanetMiningBase* base)
        : Craft(base)
    {

    }

    types::PlanetMiningBase* PlanetMiningBase::getPlanetMiningBase() const
    {
        return static_cast<types::PlanetMiningBase*>(getEntity());
    }

    std::shared_ptr<Entity> PlanetMiningBase::getPlanet() const
    {
        return createEntityPtr(GetEntity<types::Entity>(getPlanetMiningBase()->m_planetHandle));
    }

    float PlanetMiningBase::getOrbitOmega() const
    {
        return getPlanetMiningBase()->m_orbital_omega;
    }

    int PlanetMiningBase::getNumHoldingBeams() const
    {
        return getPlanetMiningBase()->m_holdingBeamCount;
    }

    void PlanetMiningBase::setPlanet(const std::shared_ptr<Entity>& ent) 
    {
        if(ent)
        {
            if(ent->isType(Entity_Planet))
            {
                PlanetMiningBase_SetPlanet(getPlanetMiningBase(), 
                                            static_cast<types::Planet*>(ent->getEntity()));
            }
        }
        PlanetMiningBase_SetPlanet(getPlanetMiningBase(), 0);
    }

    void PlanetMiningBase::setOrbitOmega(float value)
    {
        getPlanetMiningBase()->m_orbital_omega = value;
    }

    void PlanetMiningBase::setNumHoldingBeams(int value)
    {
        getPlanetMiningBase()->m_holdingBeamCount = value;
    }

    int PlanetMiningBase::index(lua_State* L, const std::string& key) const
    {
        if (key == "numberOfHoldingBeams")
        {
            lua_pushnumber(L, getNumHoldingBeams());
            return 1;
        }
        else if (key == "planet")
        {
            return entity_new(L, getPlanet());
        }
        else if (key == "orbitalOmega")
        {
            lua_pushnumber(L, getOrbitOmega());
            return 1;
        }
        return Craft::index(L, key);
    }

    int PlanetMiningBase::newindex(lua_State* L, const std::string& key)
    {
        if (key == "numberOfHoldingBeams")
        {
            setNumHoldingBeams(lua_tonumber(L, 3));
            return 0;
        }
        else if (key == "planet")
        {
            setPlanet(get_entity<Entity>(L, 3));
            return 0;
        }
        else if (key == "orbitalOmega")
        {
            setOrbitOmega(lua_tonumber(L, 3));
            return 0;
        }
        return Craft::newindex(L, key);
    }
}
