#include "ResearchStation.h"

namespace mmm
{
	void
	researchstation_register( lua_State* state )
	{
		using namespace luabind;
		
		module(state)
		[
			class_<ResearchStation, Producer, EntityPtr>( "ResearchStation" )
				.property("pods", &ResearchStation::getPods )
		];
	}
}
