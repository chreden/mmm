#pragma once

#include "Craft_Internal.h"

namespace mmm
{
    namespace types { struct SensorArray; }

    class SensorArray : public Craft
    {
    public:
        static SensorArrayPtr create(types::Entity* entity);
    private:
        explicit SensorArray(types::SensorArray* sensor);
    };
}
