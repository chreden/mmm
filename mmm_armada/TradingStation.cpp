#include "TradingStation.h"
#include "TradingStationClass_Internal.h"
#include "Type_TradingStation.h"
#include "Type_TradingStationClass.h"
#include "LuaBinding.h"

namespace mmm
{
    std::shared_ptr<TradingStation> TradingStation::create(types::Entity* entity)
    {
        return std::shared_ptr<TradingStation>(new TradingStation(static_cast<types::TradingStation*>(entity)));
    }

    TradingStation::TradingStation(types::TradingStation* station)
        : MiningStation(station)
    {

    }

    types::TradingStation* TradingStation::getTradingStation() const
    {
        return static_cast<types::TradingStation*>(getEntity());
    }

    std::shared_ptr<GameObjectClass> TradingStation::getClass() const
    {
        return std::shared_ptr<GameObjectClass>(new TradingStationClass(static_cast<types::TradingStationClass*>(getTradingStation()->m_class)));
    }

    eDockingState TradingStation::getDockingState() const
    {
        return getTradingStation()->m_DockingState;
    }

    Vector3 TradingStation::getRallyPoint() const
    {
        return getTradingStation()->m_rallyPoint;
    }

    std::shared_ptr<Entity> TradingStation::getDockedFerengi() const
    {
        return createEntityPtr(GetEntity<types::Entity>(getTradingStation()->m_ferengiNowTradingHandle));
    }

    void TradingStation::setRallyPoint(const Vector3& rallyPoint)
    {
        getTradingStation()->m_rallyPoint = rallyPoint;
    }

    int TradingStation::index(lua_State* L, const std::string& key) const
    {
        if (key == "dockedFerengi")
        {
            return entity_new(L, getDockedFerengi());
        }
        else if (key == "dockingState")
        {
            lua_pushnumber(L, getDockingState());
            return 1;
        }
        else if (key == "rallyPoint")
        {
            return vector_new(L, getRallyPoint());
        }
        return MiningStation::index(L, key);
    }

    int TradingStation::newindex(lua_State* L, const std::string& key)
    {
        if (key == "rallyPoint")
        {
            setRallyPoint(get_userdata<Vector3>(L, 3));
            return 0;
        }
        return MiningStation::newindex(L, key);
    }

    void tradingstation_register(lua_State* L)
    {
        lua_newtable(L);
        create_enum(L, "DockingState",
            {
                { "JustDocked", JustDocked },
                { "LoadCargo", LoadCargo },
                { "UnloadCargo", UnloadCargo },
                { "Exit", Exit },
            });
        lua_setglobal(L, "TradingStation");
    }
}