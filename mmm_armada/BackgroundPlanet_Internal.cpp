#include "BackgroundPlanet_Internal.h"
#include "Type_BackgroundPlanet.h"
#include "BackgroundPlanetClass_Internal.h"
#include "Type_BackgroundPlanetClass.h"

namespace mmm
{
    BackgroundPlanetPtr BackgroundPlanet::create(types::Entity* entity)
    {
        return BackgroundPlanetPtr(new BackgroundPlanet(static_cast<types::BackgroundPlanet*>(entity)));
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
