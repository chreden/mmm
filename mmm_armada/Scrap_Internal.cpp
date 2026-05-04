#include "Scrap_Internal.h"
#include "ScrapClass_Internal.h"
#include "Type_ScrapClass.h"
#include "Type_Scrap.h"

namespace mmm
{
    std::shared_ptr<Scrap> Scrap::create(types::Entity* entity)
    {
        return std::shared_ptr<Scrap>(new Scrap(static_cast<types::Scrap*>(entity)));
    }

    Scrap::Scrap(types::Scrap* scrap)
        : TerrainObject(scrap)
    {
    }

    std::shared_ptr<GameObjectClass> Scrap::getClass() const
    {
        return std::shared_ptr<GameObjectClass>(new ScrapClass(static_cast<types::ScrapClass*>(getGameObject()->m_class)));
    }
}