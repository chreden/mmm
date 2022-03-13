#include "MiningStation.h"
#include "Freighter_Internal.h"

namespace mmm
{
	void
	miningstation_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<MiningStation, bases<Producer, ResourceTransferInterface>, EntityPtr>( "Producer" )
				.def( "buildFreighter", &MiningStation::buildFreighter )
		];
	}
}
