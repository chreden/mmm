#pragma once

#include "Producer.h"

namespace mmm
{
    namespace types 
    { 
        struct Planet; 
    } 

    class Planet : public Producer
    {
    public:
        static std::shared_ptr<Planet> create(types::Entity* entity);
        std::shared_ptr<Entity> getColonyShip() const;
        eCivPopulationLevel getPopulationLevel() const;
        float getPopulation() const;
        float getMaxPopulation() const;
        std::shared_ptr<Race> getOldRace() const;
        bool getHasShields() const;
        void setPopulation(float value);

        int index(lua_State* L, const std::string& key) const override;
        int newindex(lua_State* L, const std::string& key) override;
    protected:
        explicit   Planet(types::Planet* planet);
    private:
        types::Planet* getPlanet() const;
    };

    void planet_register(lua_State* state);
}
