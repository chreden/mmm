#include "UtritiumBallClass_Internal.h"
#include "Type_UtritiumBallClass.h"

namespace mmm
{
	UtritiumBallClass::UtritiumBallClass( types::UtritiumBallClass* type )
		: TerrainObjectClass( type )
	{

	}

	types::UtritiumBallClass*
	UtritiumBallClass::getUtritiumBallClass() const
	{
		return static_cast<types::UtritiumBallClass*>( getClass() );
	}

	float 
	UtritiumBallClass::getDamage() const
	{
		return getUtritiumBallClass()->m_damageValue;
	}

	float 
	UtritiumBallClass::getRadius() const
	{
		return getUtritiumBallClass()->m_radius;
	}

	float
	UtritiumBallClass::getRotation() const
	{
		return getUtritiumBallClass()->m_rotation;
	}

	float
	UtritiumBallClass::getLifetime() const
	{
		return getUtritiumBallClass()->m_lifeTimer;
	}

	float
	UtritiumBallClass::getScalingCount() const
	{
		return getUtritiumBallClass()->m_scalingCount;
	}

	float
	UtritiumBallClass::getScalingStepSize() const
	{
		return getUtritiumBallClass()->m_scalingStepSize;
	}

	void 
	UtritiumBallClass::setDamage( float value )
	{
		getUtritiumBallClass()->m_damageValue = value;
	}

	void 
	UtritiumBallClass::setRadius( float value )
	{
		getUtritiumBallClass()->m_radius = value;
	}

	void
	UtritiumBallClass::setRotation( float value )
	{
		getUtritiumBallClass()->m_rotation = value;
	}

	void
	UtritiumBallClass::setLifetime( float value )
	{
		getUtritiumBallClass()->m_lifeTimer = value;
	}

	void
	UtritiumBallClass::setScalingStepSize( float value )
	{
		getUtritiumBallClass()->m_scalingStepSize = value;
	}

	void
	UtritiumBallClass::setScalingCount( float value )
	{
		getUtritiumBallClass()->m_scalingCount = value;
	}
}
