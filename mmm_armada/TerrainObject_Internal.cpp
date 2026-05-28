#include "TerrainObject_Internal.h"
#include "Type_TerrainObject.h"

namespace mmm
{
    std::shared_ptr<TerrainObject> TerrainObject::create(types::Entity* entity)
    {
        return std::shared_ptr<TerrainObject>(new TerrainObject(static_cast<types::TerrainObject*>(entity)));
    }

    TerrainObject::TerrainObject(types::TerrainObject* object)
        : GameObject(object)
    {

    }
}