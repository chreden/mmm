#include "Scrap_Internal.h"

namespace mmm
{
	void 
	scrap_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<Scrap, TerrainObject, EntityPtr>( "Scrap" )
		];
	}
}
