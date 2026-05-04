#pragma once

#include "GameObject_Internal.h"

namespace mmm
{
    namespace types
    {
        struct ConstructionObject;
    }

    class GameObjectClass;
    class ConstructionObject : public GameObject
    {
    public:
        static std::shared_ptr<ConstructionObject> create(types::Entity* entity);
        types::ConstructionObject* getConstructionObject() const;
        std::shared_ptr<Entity> getBuilder() const;
        std::shared_ptr<GameObjectClass> getBuildClass() const;
        int index(lua_State* L, const std::string& key) const override;
    protected:
        explicit ConstructionObject(types::ConstructionObject* object);
    };
}
