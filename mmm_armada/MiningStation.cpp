#include "MiningStation.h"
#include "Freighter_Internal.h"
#include "MiningStationClass_Internal.h"
#include "Type_MiningStationClass.h"
#include "MiningStationType.h"
#include "Type_Freighter.h"

namespace mmm
{
    MiningStationPtr MiningStation::create(types::Entity* entity)
    {
        return MiningStationPtr(new MiningStation(static_cast<types::MiningStation*>(entity)));
    }

    MiningStation::MiningStation(types::MiningStation* station)
        : Producer(station), ResourceTransferInterface(station)
    {

    }

    types::MiningStation* MiningStation::getMiningStation() const
    {
        return static_cast<types::MiningStation*>(getEntity());
    }

    std::shared_ptr<Freighter> MiningStation::buildFreighter() const
    {
        types::Freighter* freighter = (getMiningStation()->*memory_function< types::Freighter* (types::MiningStation::*)()>(Address_BuildFreighter))();
        if(freighter) 
        {
            return Freighter::create(freighter);
        }
        return {};
    }

    std::shared_ptr<GameObjectClass> MiningStation::getClass() const
    {
        return std::shared_ptr<GameObjectClass>(new MiningStationClass(static_cast<types::MiningStationClass*>(getMiningStation()->m_class)));
    }

    int MiningStation::index(lua_State* L, const std::string& key) const
    {
        if (key == "buildFreighter")
        {
            return entity_new(L, buildFreighter());
        }

        const int rti = ResourceTransferInterface::index(L, key);
        if (rti)
        {
            return rti;
        }
        return Producer::index(L, key);
    }
}
