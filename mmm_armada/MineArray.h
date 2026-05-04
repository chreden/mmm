#pragma once

#include "Craft_Internal.h"

namespace mmm
{
    namespace types { struct MineArray; }

    class MineArray : public Craft
    {
    public:
        static std::shared_ptr<MineArray> create(types::Entity* mine);
        Vector3 getHome() const;
        std::shared_ptr<Entity> getTarget() const;
        eMineArrayState getState() const;
        void setHome(const Vector3& value);
        int index(lua_State* L, const std::string& key) const override;
        int newindex(lua_State* L, const std::string& key) override;
    protected:
    private:
        explicit MineArray(types::MineArray* mine);
        types::MineArray* getMineArray() const;
    };

    void minearray_register(lua_State* L);
}