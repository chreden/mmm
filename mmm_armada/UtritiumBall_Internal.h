#pragma once

#include "TerrainObject_Internal.h"

namespace mmm
{
    namespace types { struct UtritiumBall; }

    class UtritiumBall : public TerrainObject
    {
    public:
        static std::shared_ptr<UtritiumBall> create(types::Entity* ent);
        virtual std::shared_ptr<GameObjectClass> getClass() const;

        float getTimeLeft() const;
        std::shared_ptr<Entity> getOwner() const;
        void setTimeLeft(float value);

        int index(lua_State* L, const std::string& key) const override;
        int newindex(lua_State* L, const std::string& key) override;
    protected:
        explicit UtritiumBall(types::UtritiumBall* type);
    private:
        types::UtritiumBall* getUtritiumBall() const;
    };
}
