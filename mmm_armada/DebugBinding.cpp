#include "Debug_Internal.h"

namespace mmm
{
	namespace
	{
		Debug debug;
	}

	void
	debug_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<Debug>( "_Debug" )
				.property("debugDraw", &Debug::getDebugDraw, &Debug::setDebugDraw)
				.property("commandLine", &Debug::getCommandLine )
				.def("createConsole", &Debug::createConsole)
				.def("getKeyState", &Debug::getKeyState)
				.def("circle", &Debug::circle)
				.def("connect", &Debug::connect)
				.def("disconnect", &Debug::disconnect)
		];

		globals(state)["Debug"] = &debug;
	}
}
