#include "AreaEffectObjectClass_Internal.h"
#include "Type_AreaEffectObjectClass.h"

namespace mmm
{
	AreaEffectObjectClass::AreaEffectObjectClass( types::AreaEffectObjectClass* type )
		: TerrainObjectClass( type )
	{

	}

	types::AreaEffectObjectClass* 
	AreaEffectObjectClass::getAreaEffectObjectClass() const
	{
		return static_cast<types::AreaEffectObjectClass*>( getClass() );
	}

	float 
	AreaEffectObjectClass::getRadius() const
	{
		return getAreaEffectObjectClass()->m_radius;
	}
		
	void  
	AreaEffectObjectClass::setRadius( float value )
	{
		getAreaEffectObjectClass()->m_radius = value;
	}
}
