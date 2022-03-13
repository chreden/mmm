#pragma once

#include "TerrainObjectClass_Internal.h"

namespace mmm
{
	namespace types
	{
		struct AreaEffectObjectClass;
	}

	class AreaEffectObjectClass
		: public TerrainObjectClass
	{
	public:
		explicit AreaEffectObjectClass( types::AreaEffectObjectClass* type );

		float getRadius() const;
		void  setRadius( float value );
	private:
		types::AreaEffectObjectClass* getAreaEffectObjectClass() const;
	};

	void areaeffectobjectclass_register( lua_State* state );
}
