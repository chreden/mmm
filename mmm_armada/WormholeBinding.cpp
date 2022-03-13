#include "Wormhole.h"
#include "Team_Internal.h"

namespace mmm
{
	void 
	wormhole_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<Wormhole, AreaEffectObject, EntityPtr>( "Wormhole" )
				.property( "link", &Wormhole::getPartner, &Wormhole::setPartner )
				.property( "name", &Wormhole::getName, &Wormhole::setName )
				.property( "owner", &Wormhole::getOwner, &Wormhole::setOwner )
				.property( "expireOnClose", &Wormhole::getExpireOnClose, &Wormhole::setExpireOnClose )
				.property( "deleteOnTransport", &Wormhole::getDeleteOnTransport, &Wormhole::setDeleteOnTransport )
				.property( "status", &Wormhole::getStatus )
				.scope
				[
					class_<GateStatus>("State")
						.enum_("constants")	
						[
							value("Closed", Gate_Closed),
							value("Closing", Gate_Close),
							value("Open", Gate_Open),
							value("Opening", Gate_Opening)
						]
				]

		];
	}
}
