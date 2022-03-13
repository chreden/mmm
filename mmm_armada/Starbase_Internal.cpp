#include "Starbase_Internal.h"
#include "Type_Starbase.h"

namespace mmm
{
	StarbasePtr 
	Starbase::create( types::Entity* entity )
	{
		return StarbasePtr( new Starbase( static_cast<types::Starbase*>( entity ) ) );
	}

	Starbase::Starbase( types::Starbase* starbase )
		: Shipyard( starbase )
	{

	}

	types::Starbase*
	Starbase::getStarbase( ) const
	{
		return static_cast<types::Starbase*>( getEntity() );
	}

	void
	Starbase::allocateReplacement( luabind::detail::object_rep* obj )
	{
		entity_allocate_replacement<Starbase>( obj, boost::static_pointer_cast<Starbase>( shared_from_this() ) );
	}
}
