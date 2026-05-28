#pragma once

#include "BackgroundObject_Internal.h"

namespace mmm
{
    namespace types
    {
        struct BackgroundPlanet;
    }

    class BackgroundPlanet
        : public BackgroundObject
    {
    public:
        static std::shared_ptr<BackgroundPlanet> create(types::Entity* entity);
        virtual std::shared_ptr<GameObjectClass> getClass() const;
    protected:
        explicit BackgroundPlanet(types::BackgroundPlanet* planet);
    };
}
