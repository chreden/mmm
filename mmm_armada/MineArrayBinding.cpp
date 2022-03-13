#include "MineArray.h"

namespace mmm
{
	void
	minearray_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<MineArray, Craft, EntityPtr>( "MineArray" )
				.property( "home", &MineArray::getHome, &MineArray::setHome )
				.property( "state", &MineArray::getState )
				.property( "target", &MineArray::getTarget )
				.scope
				[
					class_<eMineArrayState>("State")
						.enum_("constants")
						[
							value("DoNothing", MINE_ARRAY_DO_NOTHING),
							value("FindTarget", MINE_ARRAY_FIND_TARGET),
							value("FindHome", MINE_ARRAY_FIND_HOME)
						]
				]
		];
	}
}