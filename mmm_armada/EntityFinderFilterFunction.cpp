#include "EntityFinderFilterFunction.h"
#include "Entity_Internal.h"

namespace mmm
{
	EntityFinderFilterFunction::EntityFinderFilterFunction( luabind::object function )
		: function_( function )
	{

	}

	EntityFinderFilterFunction::~EntityFinderFilterFunction( )
	{

	}

	bool
	EntityFinderFilterFunction::call( EntityPtr entity )
	{
		return luabind::call_function<bool>( function_, entity );
	}
}
