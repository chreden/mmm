#include "BackgroundObject_Internal.h"
#include "Type_BackgroundObject.h"
#include "BackgroundObjectClass_Internal.h"
#include "Type_BackgroundObjectClass.h"

namespace mmm
{
    BackgroundObjectPtr BackgroundObject::create(types::Entity* entity)
    {
        return BackgroundObjectPtr(new BackgroundObject(static_cast<types::BackgroundObject*>(entity)));
    }

    BackgroundObject::BackgroundObject(types::BackgroundObject* object)
        : TerrainObject(object)
    {

    }

    std::shared_ptr<GameObjectClass> BackgroundObject::getClass() const
    {
        return std::shared_ptr<GameObjectClass>(new BackgroundObjectClass(static_cast<types::BackgroundObjectClass*>(getGameObject()->m_class)));
    }
}