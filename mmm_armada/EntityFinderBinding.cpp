#include "EntityFinder.h"

namespace mmm
{
	void 
	entityfinder_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<EntityFinder>( "EntityFinder" )
				.def( constructor<luabind::object>( ) )
				.def( "find", (luabind::object (EntityFinder::*)() const) &EntityFinder::find )
				.def( "find", (luabind::object (EntityFinder::*)(int) const) &EntityFinder::find )
				.def( "findOne", &EntityFinder::findOne )
		];
	}
}
