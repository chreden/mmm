#pragma once

#include "Craft_Internal.h"

namespace mmm
{
    namespace types { struct PlanetMiningBase; }

    class PlanetMiningBase : public Craft
    {
    public:
        static std::shared_ptr<PlanetMiningBase> create(types::Entity* entity);

        std::shared_ptr<Entity> getPlanet() const;
        float  getOrbitOmega() const;
        int  getNumHoldingBeams() const;

        void  setPlanet(const std::shared_ptr<Entity>& ent);
        void  setOrbitOmega(float value);
        void  setNumHoldingBeams(int value);
        int index(lua_State* L, const std::string& key) const override;
        int newindex(lua_State* L, const std::string& key) override;
    protected:
    private:
        explicit PlanetMiningBase(types::PlanetMiningBase* base);
        types::PlanetMiningBase* getPlanetMiningBase() const;
    };
}
