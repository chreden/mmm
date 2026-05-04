#include "TerrainObject_Internal.h"
#include "Type_TerrainObject.h"

namespace mmm
{
    TerrainObjectPtr TerrainObject::create(types::Entity* entity)
    {
        return TerrainObjectPtr(new TerrainObject(static_cast<types::TerrainObject*>(entity)));
    }

    TerrainObject::TerrainObject(types::TerrainObject* object)
        : GameObject(object)
    {

    }
}