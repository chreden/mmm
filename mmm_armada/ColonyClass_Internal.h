#pragma once

#include "CraftClass_Internal.h"

namespace mmm
{
	namespace types
	{
		struct ColonyClass;
	}

	class ColonyClass
		: public CraftClass
	{
	public:
		static ColonyClassPtr create( types::GameObjectClass* ptr );
	private:
		explicit ColonyClass( types::ColonyClass* colony );
	};

	void colonyclass_register( lua_State* state );
}
