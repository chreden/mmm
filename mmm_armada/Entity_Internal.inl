#pragma once

#include "LuaBinding.h"

namespace mmm
{
    template <typename T>
    std::shared_ptr<T> get_entity(lua_State* L, int index)
    {
        auto reference = get_userdata<std::shared_ptr<EntityReference>>(L, index);
        return std::static_pointer_cast<T>(createEntityPtr(reference->getEntity()));
    }
}
