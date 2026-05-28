#pragma once

#include "Producer.h"

namespace mmm
{
    namespace types
    {
        struct ConstructionRig;
    }

    class ConstructionRig : public Producer
    {
    public:
        static std::shared_ptr<ConstructionRig> create(types::Entity* entity);
        int getBeesOnboard() const;
        std::shared_ptr<Entity> getConstructionObject() const;
        void setBeesOnboard(int value);
        int index(lua_State* L, const std::string& key) const override;
    protected:
        explicit ConstructionRig(types::ConstructionRig* producer);
    private:
        types::ConstructionRig* getConstructionRig() const;
    };
}
