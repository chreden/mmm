#include "Mine.h"

namespace mmm
{
	void
	mine_register( lua_State* state )
	{
		using namespace luabind;
		module(state)
		[
			class_<Mine, Ordnance, EntityPtr>( "Mine" )
				.property( "state", &Mine::getMineStatus )
				.scope
				[
					class_<eMineStatus>("State")
						.enum_("constants")
						[
							value( "Deploy", StateDeploy ),
							value( "Detect", StateDetect ),
							value( "Chase", StateChase )
						]
				]
		];
	}
}
