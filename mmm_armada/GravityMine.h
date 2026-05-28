#pragma once

#include "Mine.h"

namespace mmm
{
    namespace types { struct GravityMine; }
    
    class GravityMine : public Mine
    {
    public:
        static std::shared_ptr<GravityMine> create(types::Entity* entity);
    protected:
        explicit GravityMine(types::GravityMine* gravityMine);
    private:
        types::GravityMine* getGravityMine() const;
    };
}
