#pragma once

#include "TerrainObjectClass_Internal.h"

namespace mmm
{
	namespace types
	{
		struct BackgroundObjectClass;
	}

	class BackgroundObjectClass
		: public TerrainObjectClass
	{
	public:
		explicit BackgroundObjectClass( types::BackgroundObjectClass* object );
	};

	void backgroundobjectclass_register( lua_State* state );
}
