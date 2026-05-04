#pragma once

#include "EntityFinderFilter.h"

namespace mmm
{
    class EntityFinderFilterObject final : public EntityFinderFilter
    {
    public:
        explicit EntityFinderFilterObject(lua_State* L, int table, int function);
        virtual ~EntityFinderFilterObject();
        bool call(const std::shared_ptr<Entity>& entity) override;
    private:
        lua_State* _L{ nullptr };
        int _table{ -2 };
        int _function{ -2 };
    };
}
