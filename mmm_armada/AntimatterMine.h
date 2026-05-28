#pragma once

#include "Mine.h"

namespace mmm
{
    namespace types { struct AntimatterMine; }

    class AntimatterMine : public Mine
    {
    public:
        static std::shared_ptr<AntimatterMine> create(types::Entity* entity);
    protected:
        explicit AntimatterMine(types::AntimatterMine* antimatterMine);
    private:
        types::AntimatterMine* getAntimatterMine() const;
    };
}