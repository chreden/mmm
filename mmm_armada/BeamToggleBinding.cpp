#include "BeamToggle.h"

namespace mmm
{
	void
	beamtoggle_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<BeamToggle, Ordnance, EntityPtr>( "BeamToggle" )
				.property( "startPosition", &BeamToggle::getStartPosition, &BeamToggle::setStartPosition )
				.property( "endPosition", &BeamToggle::getEndPosition, &BeamToggle::setEndPosition )
		];
	}
}
