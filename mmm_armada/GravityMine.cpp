#include "GravityMine.h"
#include "GravityMineType.h"

namespace mmm
{
	GravityMinePtr 
	GravityMine::create( types::Entity* entity )
	{
		return GravityMinePtr( new GravityMine( static_cast<types::GravityMine*>( entity ) ) );
	}

	GravityMine::GravityMine( types::GravityMine* gravityMine )
		: Mine( gravityMine )
	{

	}

	types::GravityMine*
	GravityMine::getGravityMine() const
	{
		return static_cast<types::GravityMine*>( getEntity() );
	}

	void
	GravityMine::allocateReplacement( luabind::detail::object_rep* obj )
	{
		entity_allocate_replacement<GravityMine>( obj, boost::static_pointer_cast<GravityMine>( shared_from_this() ) );
	}
}