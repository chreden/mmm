#include "TerrainObject_Internal.h"
#include "Type_TerrainObject.h"

namespace mmm
{
	TerrainObjectPtr 
	TerrainObject::create( types::Entity* entity )
	{
		return TerrainObjectPtr( new TerrainObject( static_cast<types::TerrainObject*>( entity ) ) );
	}

	TerrainObject::TerrainObject( types::TerrainObject* object )
		: GameObject( object )
	{

	}

	void 
	TerrainObject::allocateReplacement( luabind::detail::object_rep* object )
	{
		entity_allocate_replacement<TerrainObject>( object, boost::static_pointer_cast<TerrainObject>( shared_from_this() ) );
	}
}