#include "BlackHoleClass_Internal.h"
#include "Type_BlackHoleClass.h"

namespace mmm
{
	BlackHoleClass::BlackHoleClass( types::BlackHoleClass* type )
		: AreaEffectObjectClass( type )
	{

	}

	types::BlackHoleClass*
	BlackHoleClass::getBlackHoleClass() const
	{
		return static_cast<types::BlackHoleClass*>( getClass() );
	}

	float 
	BlackHoleClass::getGravityRadius() const
	{
		return getBlackHoleClass()->m_gravityRadius;
	}

	float
	BlackHoleClass::getEventRadius() const
	{
		return getBlackHoleClass()->m_eventRadius;
	}

	float
	BlackHoleClass::getGravityForce() const
	{
		return getBlackHoleClass()->m_gravityForce;
	}

	float
	BlackHoleClass::getRotation() const
	{
		return getBlackHoleClass()->m_rotation;
	}

	float
	BlackHoleClass::getScaleSize() const
	{
		return getBlackHoleClass()->m_scaleSize;
	}

	void 
	BlackHoleClass::setGravityRadius( float value )
	{
		getBlackHoleClass()->m_gravityRadius = value;
	}
		
	void
	BlackHoleClass::setEventRadius( float value )
	{
		getBlackHoleClass()->m_eventRadius = value;
	}
		
	void 
	BlackHoleClass::setGravityForce( float value )
	{
		getBlackHoleClass()->m_gravityForce = value;
	}
		
	void 
	BlackHoleClass::setRotation( float value )
	{
		getBlackHoleClass()->m_rotation = value;
	}

	void
	BlackHoleClass::setScaleSize( float value )
	{
		getBlackHoleClass()->m_scaleSize = value;
	}
}
