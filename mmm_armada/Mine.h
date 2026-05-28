#pragma once

#include "Ordnance.h"

namespace mmm
{
    namespace types { struct Mine; }

    class Mine : public Ordnance
    {
    public:
        static std::shared_ptr<Mine> create(types::Entity* entity);
        eMineStatus getMineStatus() const;
        int index(lua_State* L, const std::string& key) const override;
    protected:
        explicit Mine(types::Mine* mine);
    private:
        types::Mine* getMine() const;
    };

    void mine_register(lua_State* state);
}
