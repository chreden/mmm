#include "LatinumNebulaClass_Internal.h"
#include "Type_LatinumNebulaClass.h"

namespace mmm
{
	LatinumNebulaClass::LatinumNebulaClass( types::LatinumNebulaClass* nebula )
		: TerrainObjectClass( nebula )
	{

	}

	float 
	LatinumNebulaClass::getRotationSpeed() const
	{
		return getLatinumNebula()->m_rotationSpeed;
	}

	void
	LatinumNebulaClass::setRotationSpeed( float value )
	{
		getLatinumNebula()->m_rotationSpeed = value;
	}

	types::LatinumNebulaClass* 
	LatinumNebulaClass::getLatinumNebula() const
	{
		return static_cast<types::LatinumNebulaClass*>( getClass() );
	}
}
