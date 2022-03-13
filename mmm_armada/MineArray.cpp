#include "MineArray.h"
#include "MineArrayType.h"

namespace mmm
{
	MineArrayPtr
	MineArray::create( types::Entity* mine )
	{
		return MineArrayPtr( new MineArray( static_cast<types::MineArray*>( mine ) ) );
	}

	MineArray::MineArray( types::MineArray* mine )
		: Craft( mine )
	{

	}

	void
	MineArray::allocateReplacement( luabind::detail::object_rep* object )
	{
		entity_allocate_replacement<MineArray>( object, boost::static_pointer_cast<MineArray>( shared_from_this() ) );
	}

	types::MineArray*
	MineArray::getMineArray() const
	{
		return static_cast<types::MineArray*>( getEntity() );
	}

	Vector3
	MineArray::getHome() const
	{
		return getMineArray()->m_home;
	}

	EntityPtr
	MineArray::getTarget() const
	{
		return createEntityPtr( GetEntity<types::Entity>( getMineArray()->m_target ) );
	}

	eMineArrayState
	MineArray::getState() const
	{
		return getMineArray()->m_state;
	}

	void
	MineArray::setHome( const Vector3& value )
	{
		getMineArray()->m_home = value;
	}
}
