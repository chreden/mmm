#pragma once

#include "BackgroundObjectClass_Internal.h"

namespace mmm
{
	namespace types
	{	
		struct BackgroundPlanetClass;
	}

	class BackgroundPlanetClass
		: public BackgroundObjectClass
	{
	public:
		explicit BackgroundPlanetClass( types::BackgroundPlanetClass* planet );

		float getRotationRate( ) const;
		float getCrewModifier( ) const;

		void setRotationRate( float value );
		void setCrewModifier( float value );
	private:
		types::BackgroundPlanetClass* getBackgroundPlanetClass() const;
	};

	void backgroundplanetclass_register( lua_State* state );
}
