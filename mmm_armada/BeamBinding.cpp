#include "Beam_Internal.h"

namespace mmm
{
	void
	beam_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<Beam, Ordnance, EntityPtr>( "Beam" )
				.property("startPosition", &Beam::getStartPos )
				.property("endPosition", &Beam::getEndPos )
		];
	}
}
