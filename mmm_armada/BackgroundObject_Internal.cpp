#include "BackgroundObject_Internal.h"
#include "Type_BackgroundObject.h"
#include "BackgroundObjectClass_Internal.h"
#include "Type_BackgroundObjectClass.h"

namespace mmm
{
	BackgroundObjectPtr 
	BackgroundObject::create( types::Entity* entity )
	{
		return BackgroundObjectPtr( new BackgroundObject( static_cast<types::BackgroundObject*>( entity ) ) );
	}

	BackgroundObject::BackgroundObject( types::BackgroundObject* object )
		: TerrainObject( object )
	{

	}

	GameObjectClassPtr 
	BackgroundObject::getClass() const
	{
		return GameObjectClassPtr( new BackgroundObjectClass( static_cast<types::BackgroundObjectClass*>( getGameObject()->m_class ) ) );
	}

	void 
	BackgroundObject::allocateReplacement( luabind::detail::object_rep* object )
	{
		entity_allocate_replacement<BackgroundObject>( object, boost::static_pointer_cast<BackgroundObject>( shared_from_this() ) );
	}
}