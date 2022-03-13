#include "AreaEffectObject_Internal.h"
#include "AreaEffectObjectClass_Internal.h"
#include "Type_AreaEffectObjectClass.h"
#include "Type_AreaEffectObject.h"

namespace mmm
{
	AreaEffectObjectPtr
	AreaEffectObject::create( types::Entity* entity )
	{
		return AreaEffectObjectPtr( new AreaEffectObject( static_cast<types::AreaEffectObject*>( entity ) ) );
	}

	AreaEffectObject::AreaEffectObject( types::AreaEffectObject* object )
		: TerrainObject( object )
	{

	}

	GameObjectClassPtr 
	AreaEffectObject::getClass() const
	{
		return GameObjectClassPtr( new AreaEffectObjectClass( static_cast<types::AreaEffectObjectClass*>( getGameObject()->m_class ) ) );
	}

	void
	AreaEffectObject::allocateReplacement( luabind::detail::object_rep* obj )
	{
		entity_allocate_replacement<AreaEffectObject>( obj, boost::static_pointer_cast<AreaEffectObject>( shared_from_this() ) );
	}
}