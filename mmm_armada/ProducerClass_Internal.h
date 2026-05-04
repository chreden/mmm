#pragma once

#include "CraftClass_Internal.h"

namespace mmm
{
    namespace types
    {
        struct ProducerClass;
    }

    class ProducerClass : public CraftClass
    {
    public:
        static ProducerClassPtr create(types::GameObjectClass* ptr);
        void setitem(int index, const std::shared_ptr<GameObjectClass>& obj);
        int index(lua_State* L, const std::string& key) const override;
    protected:
        explicit ProducerClass(types::ProducerClass* producer);
    private:
        types::ProducerClass* getProducerClass() const;
    };
}
