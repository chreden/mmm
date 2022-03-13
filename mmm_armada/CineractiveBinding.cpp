#include "Cineractive_Internal.h"
#include "Path_Internal.h"

namespace mmm
{
	namespace
	{
		Cineractive cineractive;
	}

	void 
	cineractive_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<Cineractive>( "_Cineractive" )
				.property( "active", &Cineractive::isActive, &Cineractive::setActive )
				.property( "skippable", &Cineractive::isSkippable, &Cineractive::setSkippable )
				.def( "lookAt", (void(Cineractive::*)(EntityPtr))&Cineractive::lookAt )
				.def( "lookAt", (void(Cineractive::*)(const Vector3&))&Cineractive::lookAt )
				.def( "lookFrom", (void(Cineractive::*)(EntityPtr))&Cineractive::lookFrom )
				.def( "lookFrom", (void(Cineractive::*)(const Vector3&))&Cineractive::lookFrom )
				.def( "lookFrom", (void(Cineractive::*)(const Path&, float))&Cineractive::lookFrom )
				.def( "setCameraOffset", &Cineractive::setCameraOffset )
				.def( "fadeIn", &Cineractive::fadeIn )
				.def( "fadeOut", &Cineractive::fadeOut )
		];

		globals(state)["Cineractive"] = &cineractive;
	}	
}
