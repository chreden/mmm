#include "ProducerClass_Internal.h"
#include "Type_ProducerClass.h"
#include "LuaBinding.h"

namespace mmm
{
    namespace
    {
        int producerclass_setitem(lua_State* L)
        {
            auto self = get_userdata<std::shared_ptr<ProducerClass>>(L, 1);
            self->setitem(lua_tonumber(L, 2), get_userdata<std::shared_ptr<GameObjectClass>>(L, 3));
            return 0;
        }
    }

    ProducerClassPtr ProducerClass::create(types::GameObjectClass* ptr)
    {
        return ProducerClassPtr(new ProducerClass(static_cast<types::ProducerClass*>(ptr)));
    }

    ProducerClass::ProducerClass(types::ProducerClass* producer)
        : CraftClass(producer)
    {
    }

    types::ProducerClass* ProducerClass::getProducerClass() const
    {
        return static_cast<types::ProducerClass*>(getClass());
    }

    void ProducerClass::setitem(int index, const std::shared_ptr<GameObjectClass>& obj)
    {
        //This is only done when fleetops is present. We need to make sure that
        //we detect FO.
        types::GameObjectClass*** redirect = reinterpret_cast<types::GameObjectClass***>(getProducerClass()->buildItem);
        types::GameObjectClass** items = *redirect;
        items[index] = obj->getClass();
    }

    int ProducerClass::index(lua_State* L, const std::string& key) const
    {
        if (key == "setitem")
        {
            lua_pushcfunction(L, producerclass_setitem);
            return 1;
        }
        return CraftClass::index(L, key);
    }
}
