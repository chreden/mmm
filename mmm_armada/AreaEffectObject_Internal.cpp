#include "AreaEffectObject_Internal.h"
#include "AreaEffectObjectClass_Internal.h"
#include "Type_AreaEffectObjectClass.h"
#include "Type_AreaEffectObject.h"

namespace mmm
{
    std::shared_ptr<AreaEffectObject> AreaEffectObject::create(types::Entity* entity)
    {
        return std::shared_ptr<AreaEffectObject>(new AreaEffectObject(static_cast<types::AreaEffectObject*>(entity)));
    }

    AreaEffectObject::AreaEffectObject(types::AreaEffectObject* object)
        : TerrainObject(object)
    {

    }

    std::shared_ptr<GameObjectClass> AreaEffectObject::getClass() const
    {
        return std::shared_ptr<GameObjectClass>(new AreaEffectObjectClass(static_cast<types::AreaEffectObjectClass*>(getGameObject()->m_class)));
    }
}