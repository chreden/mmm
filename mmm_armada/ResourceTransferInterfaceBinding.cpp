#include "ResourceTransferInterface.h"
#include "Entity_Internal.h"
#include "OrientedQueue.h"

namespace mmm
{
	void
	resourcetransferinterface_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<ResourceTransferInterface>( "ResourceTransferInterface" )
				.property( "dockedShip", &ResourceTransferInterface::getDockedShip )	
				.property( "isShipDocked", &ResourceTransferInterface::isShipDocked )
				.property( "miningQueue", &ResourceTransferInterface::getMiningQueue )
				.property( "transferRates", &ResourceTransferInterface::getResourceRates )
		];
	}
}
