#include "SensorArray.h"
#include "Type_SensorArray.h"

namespace mmm
{
    std::shared_ptr<SensorArray> SensorArray::create(types::Entity* entity)
    {
        return std::shared_ptr<SensorArray>(new SensorArray(static_cast<types::SensorArray*>(entity)));
    }

    SensorArray::SensorArray(types::SensorArray* sensor)
        : Craft(sensor)
    {

    }
}
