#include "Mine.h"
#include "MineType.h"

namespace mmm
{
	MinePtr 
	Mine::create( types::Entity* entity )
	{
		return MinePtr( new Mine( static_cast<types::Mine*>( entity ) ) );
	}

	Mine::Mine( types::Mine* mine )
		: Ordnance( mine )
	{

	}

	types::Mine*
	Mine::getMine( ) const
	{
		return static_cast<types::Mine*>( getEntity() );
	}

	void
	Mine::allocateReplacement( luabind::detail::object_rep* obj )
	{
		entity_allocate_replacement<Mine>( obj, boost::static_pointer_cast<Mine>( shared_from_this() ) );
	}

	eMineStatus 
	Mine::getMineStatus() const
	{
		return getMine()->m_mineStatus;
	}
}