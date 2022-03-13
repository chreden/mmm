#include "ScrapClass_Internal.h"
#include "Type_ScrapClass.h"

namespace mmm
{
	ScrapClass::ScrapClass( types::ScrapClass* obj )
		: TerrainObjectClass( obj )
	{

	}

	types::ScrapClass*
	ScrapClass::getScrapClass() const
	{
		return static_cast<types::ScrapClass*>( getClass() );
	}

	float	
	ScrapClass::getRotationSpeed( ) const
	{
		return getScrapClass()->m_rotation_speed;
	}

	void	
	ScrapClass::setRotationSpeed( float value )
	{
		getScrapClass()->m_rotation_speed = value;
	}
}
