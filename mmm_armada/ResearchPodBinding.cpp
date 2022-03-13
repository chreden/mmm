#include "ResearchPod_Internal.h"

namespace mmm
{
	void
	researchpod_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<ResearchPod, Craft, EntityPtr>( "ResearchPod" )
				.property( "station", &ResearchPod::getStation )
		];
	}
}