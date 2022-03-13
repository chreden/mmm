#include "Test.h"

namespace mmm
{
	namespace
	{
		Test test;
	}

	void
	test_register( lua_State* state )
	{
		using namespace luabind;
		module(state)
		[
			class_<Test>( "_Test" )
				.def( "isTrue", &Test::isTrue )
				.def( "isFalse", &Test::isFalse )
				.def( "run", &Test::runAll )
				.def( "add", &Test::add )
		];

		globals(state)["Test"] = &test;
	}
}