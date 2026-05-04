#include "LatinumNebula_Internal.h"
#include "Type_LatinumNebula.h"
#include "Type_LatinumNebulaClass.h"
#include "LatinumNebulaClass_Internal.h"

namespace mmm
{
    LatinumNebulaPtr LatinumNebula::create(types::Entity* entity)
    {
        return LatinumNebulaPtr(new LatinumNebula(static_cast<types::LatinumNebula*>(entity)));
    }

    LatinumNebula::LatinumNebula(types::LatinumNebula* nebula)
        : TerrainObject(nebula)
    {
    }

    std::shared_ptr<GameObjectClass> LatinumNebula::getClass() const
    {
        return std::shared_ptr<GameObjectClass>(new LatinumNebulaClass(static_cast<types::LatinumNebulaClass*>(getGameObject()->m_class)));
    }
}
