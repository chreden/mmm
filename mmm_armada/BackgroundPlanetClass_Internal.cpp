#include "BackgroundPlanetClass_Internal.h"
#include "Type_BackgroundPlanetClass.h"

namespace mmm
{
	BackgroundPlanetClass::BackgroundPlanetClass( types::BackgroundPlanetClass* planet )
		: BackgroundObjectClass( planet )
	{

	}

	types::BackgroundPlanetClass* 
	BackgroundPlanetClass::getBackgroundPlanetClass() const
	{
		return static_cast<types::BackgroundPlanetClass*>( getClass() );
	}
		
	float 
	BackgroundPlanetClass::getRotationRate( ) const
	{
		return getBackgroundPlanetClass()->rotationRate;
	}

	float 
	BackgroundPlanetClass::getCrewModifier( ) const
	{
		return getBackgroundPlanetClass()->crewModifier;
	}

	void 
	BackgroundPlanetClass::setRotationRate( float value )
	{
		getBackgroundPlanetClass()->rotationRate = value;
	}

	void 
	BackgroundPlanetClass::setCrewModifier( float value )
	{
		getBackgroundPlanetClass()->crewModifier = value;
	}
}
