#include "EntityFinderFilter.h"

namespace mmm
{
    class EntityFinderFilterFunction final : public EntityFinderFilter
    {
    public:
        explicit EntityFinderFilterFunction(lua_State* L, int index);
        virtual ~EntityFinderFilterFunction();
        bool call(const std::shared_ptr<Entity>& entity) override;
    private:
        lua_State* _L{ nullptr };
        int _index{ -2 };
    };
}
