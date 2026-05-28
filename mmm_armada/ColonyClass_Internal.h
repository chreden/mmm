#pragma once

#include "CraftClass_Internal.h"

namespace mmm
{
    namespace types
    {
        struct ColonyClass;
    }

    class ColonyClass : public CraftClass
    {
    public:
        static std::shared_ptr<ColonyClass> create(types::GameObjectClass* ptr);
    private:
        explicit ColonyClass(types::ColonyClass* colony);
    };
}
