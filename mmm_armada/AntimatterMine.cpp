#include "AntimatterMine.h"
#include "AntimatterMineType.h"

namespace mmm
{
	AntimatterMinePtr
	AntimatterMine::create( types::Entity* entity )
	{
		return AntimatterMinePtr( new AntimatterMine( static_cast<types::AntimatterMine*>( entity ) ) );
	}

	AntimatterMine::AntimatterMine( types::AntimatterMine* antimatterMine )
		: Mine( antimatterMine )
	{

	}

	types::AntimatterMine*
	AntimatterMine::getAntimatterMine( ) const
	{
		return static_cast<types::AntimatterMine*>( getEntity() );
	}

	void
	AntimatterMine::allocateReplacement( luabind::detail::object_rep* obj )
	{
		entity_allocate_replacement<AntimatterMine>( obj, boost::static_pointer_cast<AntimatterMine>( shared_from_this() ) );
	}
}