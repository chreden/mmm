#pragma once

#include "GameObjectClass_Internal.h"

namespace mmm
{
	namespace types
	{
		struct CraftClass;
	}

	class CraftClass
		: public GameObjectClass
	{
	public:
		static CraftClassPtr create( types::GameObjectClass* ptr );
	protected:
		explicit CraftClass( types::CraftClass* craftClass );
	private:
		types::CraftClass* getCraftClass() const;
	};

	void craftclass_register( lua_State* state );
}
