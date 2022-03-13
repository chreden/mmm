#include "Load_Internal.h"

namespace mmm
{
	namespace 
	{
		Load load;
	}

	void
	load_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<Load>( "LoadData" )
				.def( "load", &Load::doLoad )
				.def( "readString", &Load::read<std::string> )
				.def( "readNumber", &Load::read<float> )
				.def( "readBoolean", &Load::read<bool> )
				.property( "position", &Load::getLength, &Load::setRead )
				
		];

		globals(state)["Load"] = &load;
	}
}
