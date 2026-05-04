#pragma once

#include "Craft_Internal.h"

namespace mmm
{
    namespace types
    {
        struct Colony;
    }

    class Colony : public Craft
    {
    public:
        static ColonyPtr create(types::Entity* entity);

        std::shared_ptr<Entity> getPlanet() const;
        int getColonists() const;
        int getInitialColonists() const;
        float getInitialPopulation() const;

        void setColonists(int value);
        void setInitialColonists(int value);
        void setInitialPopulation(float value);

        int index(lua_State* L, const std::string& key) const override;
        int newindex(lua_State* L, const std::string& key) override;
    protected:
        explicit Colony(types::Colony* colony);
    private:
        types::Colony* getColony() const;
    };
}
