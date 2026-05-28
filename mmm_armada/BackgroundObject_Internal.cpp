#include "BackgroundObject_Internal.h"
#include "Type_BackgroundObject.h"
#include "BackgroundObjectClass_Internal.h"
#include "Type_BackgroundObjectClass.h"

namespace mmm
{
    std::shared_ptr<BackgroundObject> BackgroundObject::create(types::Entity* entity)
    {
        return std::shared_ptr<BackgroundObject>(new BackgroundObject(static_cast<types::BackgroundObject*>(entity)));
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