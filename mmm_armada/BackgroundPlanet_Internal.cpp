#include "BackgroundPlanet_Internal.h"
#include "Type_BackgroundPlanet.h"
#include "BackgroundPlanetClass_Internal.h"
#include "Type_BackgroundPlanetClass.h"

namespace mmm
{
    std::shared_ptr<BackgroundPlanet> BackgroundPlanet::create(types::Entity* entity)
    {
        return std::shared_ptr<BackgroundPlanet>(new BackgroundPlanet(static_cast<types::BackgroundPlanet*>(entity)));
    }

    BackgroundPlanet::BackgroundPlanet(types::BackgroundPlanet* planet)
        : BackgroundObject(planet)
    {

    }

    std::shared_ptr<GameObjectClass> BackgroundPlanet::getClass() const
    {
        return std::shared_ptr<GameObjectClass>(new BackgroundPlanetClass(static_cast<types::BackgroundPlanetClass*>(getGameObject()->m_class)));
    }
}
