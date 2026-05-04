#pragma once

#include "MiningStation.h"

namespace mmm
{
    namespace types { struct TradingStation; }

    class TradingStation : public MiningStation
    {
    public:
        static TradingStationPtr create(types::Entity* entity);
        virtual std::shared_ptr<GameObjectClass> getClass() const;

        eDockingState getDockingState() const;
        Vector3  getRallyPoint() const;
        std::shared_ptr<Entity>  getDockedFerengi() const;
        void  setRallyPoint(const Vector3& rallyPoint);

        int index(lua_State* L, const std::string& key) const override;
        int newindex(lua_State* L, const std::string& key) override;
    protected:
        explicit TradingStation(types::TradingStation* station);
    private:
        types::TradingStation* getTradingStation() const;
    };

    void tradingstation_register(lua_State* state);
}