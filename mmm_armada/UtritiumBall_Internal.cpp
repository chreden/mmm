#include "UtritiumBall_Internal.h"
#include "UtritiumBallClass_Internal.h"
#include "Type_UtritiumBall.h"
#include "Type_UtritiumBallClass.h"

namespace mmm
{
	UtritiumBallPtr 
	UtritiumBall::create( types::Entity* ent )
	{
		return UtritiumBallPtr( new UtritiumBall( static_cast<types::UtritiumBall*>( ent ) ) );
	}

	UtritiumBall::UtritiumBall( types::UtritiumBall* type )
		: TerrainObject( type )
	{

	}

	GameObjectClassPtr 
	UtritiumBall::getClass() const
	{
		return GameObjectClassPtr( new UtritiumBallClass( static_cast<types::UtritiumBallClass*>( getGameObject()->m_class ) ) );
	}

	types::UtritiumBall*
	UtritiumBall::getUtritiumBall() const
	{
		return static_cast<types::UtritiumBall*>( getEntity() );
	}

	float 
	UtritiumBall::getTimeLeft() const
	{
		return getUtritiumBall()->m_time_left;
	}

	EntityPtr
	UtritiumBall::getOwner() const
	{
		return createEntityPtr( GetEntity<types::Entity>( getUtritiumBall()->m_ownerHandle ) );
	}

	void 
	UtritiumBall::setTimeLeft( float value )
	{
		getUtritiumBall()->m_time_left = value;
	}

	void
	UtritiumBall::allocateReplacement( luabind::detail::object_rep* obj )
	{
		entity_allocate_replacement<UtritiumBall>( obj, boost::static_pointer_cast<UtritiumBall>( shared_from_this() ) );
	}
}
