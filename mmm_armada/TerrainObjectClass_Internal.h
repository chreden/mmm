#pragma once

#include "GameObjectClass_Internal.h"

namespace mmm
{
	namespace types
	{
		struct TerrainObjectClass;
	}

	class TerrainObjectClass
		: public GameObjectClass
	{
	public:
		explicit TerrainObjectClass( types::TerrainObjectClass* object );
	private:
		types::TerrainObjectClass* getTerrainObjectClass() const;
	};

	void terrainobjectclass_register( lua_State* state );
}
