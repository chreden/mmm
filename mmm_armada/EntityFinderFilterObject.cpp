#include "EntityFinderFilterObject.h"
#include "Entity_Internal.h"

namespace mmm
{
	EntityFinderFilterObject::EntityFinderFilterObject( luabind::object table, luabind::object function )
		: table_( table ), function_( function )
	{
		
	}

	EntityFinderFilterObject::~EntityFinderFilterObject( )
	{

	}

	bool
	EntityFinderFilterObject::call( EntityPtr entity )
	{
		return luabind::call_function<bool>( function_, table_, entity );
	}
}
