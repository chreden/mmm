#include "LatinumNebula_Internal.h"
#include "Type_LatinumNebula.h"
#include "Type_LatinumNebulaClass.h"
#include "LatinumNebulaClass_Internal.h"

namespace mmm
{
	LatinumNebulaPtr 
	LatinumNebula::create( types::Entity* entity )
	{
		return LatinumNebulaPtr( new LatinumNebula( static_cast<types::LatinumNebula*>( entity ) ) );
	}

	LatinumNebula::LatinumNebula( types::LatinumNebula* nebula )
		: TerrainObject( nebula )
	{

	}

	GameObjectClassPtr 
	LatinumNebula::getClass() const
	{
		return GameObjectClassPtr( new LatinumNebulaClass( static_cast<types::LatinumNebulaClass*>( getGameObject()->m_class ) ) );
	}

	void 
	LatinumNebula::allocateReplacement( luabind::detail::object_rep* object )
	{
		entity_allocate_replacement<LatinumNebula>( object, boost::static_pointer_cast<LatinumNebula>( shared_from_this() ) );
	}
}
