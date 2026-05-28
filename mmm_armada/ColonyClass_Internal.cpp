#include "ColonyClass_Internal.h"
#include "Type_ColonyClass.h"

namespace mmm
{
    std::shared_ptr<ColonyClass> ColonyClass::create(types::GameObjectClass* ptr)
    {
        return std::shared_ptr<ColonyClass>(new ColonyClass(static_cast<types::ColonyClass*>(ptr)));
    }

    ColonyClass::ColonyClass(types::ColonyClass* colony)
        : CraftClass(colony)
    {
    }
}
