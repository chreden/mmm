#include "Scavenger.h"
#include "Type_Scavenger.h"

namespace mmm
{
	ScavengerPtr
	Scavenger::create( types::Entity* scavenger )
	{
		return ScavengerPtr( new Scavenger( static_cast<types::Scavenger*>( scavenger ) ) );
	}

	Scavenger::Scavenger( types::Scavenger* scavenger )
		: Craft( scavenger )
	{

	}

	void
	Scavenger::allocateReplacement( luabind::detail::object_rep* object )
	{
		entity_allocate_replacement<Scavenger>( object, boost::static_pointer_cast<Scavenger>(shared_from_this()) );
	}
}