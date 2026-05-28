#include "AntimatterMine.h"
#include "AntimatterMineType.h"

namespace mmm
{
    std::shared_ptr<AntimatterMine> AntimatterMine::create(types::Entity* entity)
    {
        return std::shared_ptr<AntimatterMine>(new AntimatterMine(static_cast<types::AntimatterMine*>(entity)));
    }

    AntimatterMine::AntimatterMine(types::AntimatterMine* antimatterMine)
        : Mine(antimatterMine)
    {
    }

    types::AntimatterMine* AntimatterMine::getAntimatterMine() const
    {
        return static_cast<types::AntimatterMine*>(getEntity());
    }
}