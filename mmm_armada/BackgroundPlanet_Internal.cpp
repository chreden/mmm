#include "BackgroundPlanet_Internal.h"
#include "Type_BackgroundPlanet.h"
#include "BackgroundPlanetClass_Internal.h"
#include "Type_BackgroundPlanetClass.h"

namespace mmm
{
	BackgroundPlanetPtr 
	BackgroundPlanet::create( types::Entity* entity )
	{
		return BackgroundPlanetPtr( new BackgroundPlanet( static_cast<types::BackgroundPlanet*>( entity ) ) );
	}

	BackgroundPlanet::BackgroundPlanet( types::BackgroundPlanet* planet )
		: BackgroundObject( planet )
	{

	}

	GameObjectClassPtr 
	BackgroundPlanet::getClass() const
	{
		return GameObjectClassPtr( new BackgroundPlanetClass( static_cast<types::BackgroundPlanetClass*>( getGameObject()->m_class ) ) );
	}

	void 
	BackgroundPlanet::allocateReplacement( luabind::detail::object_rep* object )
	{
		entity_allocate_replacement<BackgroundPlanet>( object, boost::static_pointer_cast<BackgroundPlanet>( shared_from_this() ) );
	}
}
