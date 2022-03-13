#include "ConstructionObject_Internal.h"
#include "Type_ConstructionObject.h"
#include "Type_CraftClass.h"
#include "GameObjectClass_Internal.h"

namespace mmm
{
	//0001:000a2480       ?SetBuildClass@ConstructionObject@@QAEXPBVCraftClass@@@Z 004a3480 f   ConstructionObject.obj

	ConstructionObjectPtr 
	ConstructionObject::create( types::Entity* entity )
	{
		return ConstructionObjectPtr( new ConstructionObject( static_cast<types::ConstructionObject*>( entity ) ) );
	}

	ConstructionObject::ConstructionObject( types::ConstructionObject* object )
		: GameObject( object )
	{

	}

	types::ConstructionObject* 
	ConstructionObject::getConstructionObject() const
	{
		return static_cast<types::ConstructionObject*>( getEntity() );
	}

	void
	ConstructionObject::allocateReplacement( luabind::detail::object_rep* obj )
	{
		entity_allocate_replacement<ConstructionObject>( obj, boost::static_pointer_cast<ConstructionObject>( shared_from_this() ) );
	}

	EntityPtr 
	ConstructionObject::getBuilder() const
	{
		return createEntityPtr( GetEntity<types::GameObject>( getConstructionObject()->m_rigHandle ) );
	}

	GameObjectClassPtr 
	ConstructionObject::getBuildClass() const
	{
		return createGameObjectClassPtr( getConstructionObject()->m_pBuildClass );
	}
}