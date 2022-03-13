#pragma once

#include "TerrainObjectClass_Internal.h"

namespace mmm
{
	namespace types
	{
		struct UtritiumBallClass;
	}

	class UtritiumBallClass
		: public TerrainObjectClass
	{
	public:
		explicit UtritiumBallClass( types::UtritiumBallClass* type );

		float getDamage() const;
		float getRadius() const;
		float getRotation() const;
		float getLifetime() const;
		float getScalingCount() const;
		float getScalingStepSize() const;

		void setDamage( float value );
		void setRadius( float value );
		void setRotation( float value );
		void setLifetime( float value );
		void setScalingCount( float value );
		void setScalingStepSize( float value );
	private:
		types::UtritiumBallClass* getUtritiumBallClass() const;
	};

	void utritiumballclass_register( lua_State* state );
}
