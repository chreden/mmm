#include "ResourceInterface_Internal.h"
#include "Entity_Internal.h"

namespace mmm
{
	void
	resourceinterface_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<ResourceInterface>( "ResourceInterface" )
				.property( "infinite", &ResourceInterface::getResourceIsInfinite, &ResourceInterface::setResourceIsInfinite )
				.property( "miner", &ResourceInterface::getMiner )
				.property( "orbitalStation", &ResourceInterface::getOrbitalStation )
				.property( "resources", &ResourceInterface::getResources )
		];
	}
}
