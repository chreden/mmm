#include "Bullet.h"
#include "Type_Bullet.h"

namespace mmm
{
	BulletPtr
	Bullet::create( types::Entity* entity )
	{
		return BulletPtr( new Bullet( static_cast<types::Bullet*>( entity ) ) );
	}

	Bullet::Bullet( types::Bullet* bullet )
		: Ordnance( bullet )
	{

	}

	types::Bullet*
	Bullet::getBullet() const
	{
		return static_cast<types::Bullet*>( getEntity() );
	}

	void
	Bullet::allocateReplacement( luabind::detail::object_rep* obj )
	{
		entity_allocate_replacement<Bullet>( obj, boost::static_pointer_cast<Bullet>( shared_from_this() ) );
	}

	Vector3 
	Bullet::getStartPosition() const
	{
		return getBullet()->startPos;
	}
	
	Vector3 
	Bullet::getCurrentPosition() const
	{
		return getBullet()->currentPos;
	}

	void 
	Bullet::setStartPosition( const Vector3& position )
	{
		getBullet()->startPos = position;
	}
	
	void 
	Bullet::setCurrentPosition( const Vector3& position )
	{
		getBullet()->currentPos = position;
	}
}
