#pragma once

#include "Craft_Internal.h"

namespace mmm
{
    namespace types { struct CargoShip; }

    class CargoShip : public Craft
    {
    public:
        static CargoShipPtr create(types::Entity* entity);
        //Properties that are part of the actual cargo ship
        std::shared_ptr<Entity>	getStartStation() const;
        std::shared_ptr<Entity>	getDestinationStation() const;
        bool getIsTrading() const;
        float getMaxCargo() const;
        eResource getNextResource() const;
        float getCargoAmount() const;
        eResource getResource() const;
        std::string getCargoName() const;
        bool getIsFull() const;

        int index(lua_State* L, const std::string& key) const override;
    protected:
        explicit CargoShip(types::CargoShip* cargoShip);
    private:
        types::CargoShip* getCargoShip() const;
    };
}
