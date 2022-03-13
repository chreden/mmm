#pragma once

#include "TerrainObjectClass_Internal.h"

namespace mmm
{
	namespace types
	{
		struct LatinumNebulaClass;
	}

	class LatinumNebulaClass
		: public TerrainObjectClass
	{
	public:
		explicit LatinumNebulaClass( types::LatinumNebulaClass* nebula );

		float getRotationSpeed() const;
		void  setRotationSpeed( float value );
	private:
		types::LatinumNebulaClass* getLatinumNebula() const;
	};

	void latinumnebulaclass_register( lua_State* state );
}
