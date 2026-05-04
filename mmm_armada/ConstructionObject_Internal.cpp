#include "ConstructionObject_Internal.h"
#include "Type_ConstructionObject.h"
#include "Type_CraftClass.h"
#include "GameObjectClass_Internal.h"

namespace mmm
{
    //0001:000a2480       ?SetBuildClass@ConstructionObject@@QAEXPBVCraftClass@@@Z 004a3480 f   ConstructionObject.obj

    std::shared_ptr<ConstructionObject> ConstructionObject::create( types::Entity* entity )
    {
        return std::shared_ptr<ConstructionObject>(new ConstructionObject(static_cast<types::ConstructionObject*>(entity)));
    }

    ConstructionObject::ConstructionObject(types::ConstructionObject* object)
        : GameObject(object)
    {
    }

    types::ConstructionObject* ConstructionObject::getConstructionObject() const
    {
        return static_cast<types::ConstructionObject*>(getEntity());
    }

    std::shared_ptr<Entity> ConstructionObject::getBuilder() const
    {
        return createEntityPtr(GetEntity<types::GameObject>(getConstructionObject()->m_rigHandle));
    }

    std::shared_ptr<GameObjectClass> ConstructionObject::getBuildClass() const
    {
        return createGameObjectClassPtr(getConstructionObject()->m_pBuildClass);
    }

    int ConstructionObject::index(lua_State* L, const std::string& key) const
    {
        if (key == "builder")
        {
            return entity_new(L, getBuilder());
        }
        else if (key == "buildClass")
        {
            return gameobjectclass_new(L, getBuildClass());
        }
        return GameObject::index(L, key);
    }
}