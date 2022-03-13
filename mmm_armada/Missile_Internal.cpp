#include "Missile_Internal.h"
#include "Type_Missile.h"


namespace mmm
{
	MissilePtr
	Missile::create( types::Entity* entity )
	{
		return MissilePtr( new Missile( static_cast<types::Missile*>( entity ) ) );
	}

	Missile::Missile( types::Missile* missile )
		: Ordnance( missile )
	{

	}

	types::Missile* 
	Missile::getMissile() const
	{
		return static_cast<types::Missile*>( getEntity() );
	}

	void
	Missile::allocateReplacement( luabind::detail::object_rep* obj )
	{
		entity_allocate_replacement<Missile>( obj, boost::static_pointer_cast<Missile>( shared_from_this() ) );
	}

	Vector3
	Missile::getOmega() const
	{
		return getMissile()->omega;
	}

	float
	Missile::getSeekTimer( ) const
	{
		return getMissile()->seekTimer;
	}

	float
	Missile::getTurnLim2() const
	{
		return getMissile()->turnLim2;
	}

	void
	Missile::setOmega( const Vector3& value )
	{
		getMissile()->omega = value;
	}

	void
	Missile::setTurnLim2( float value )
	{
		getMissile()->turnLim2 = value;
	}

}
