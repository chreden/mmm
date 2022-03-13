#include "Path_Internal.h"

namespace mmm
{
	void 
	path_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<Path>( "Path" )
                .def( constructor<>() )
				.def( constructor<std::string>() )
				.property( "count", &Path::count )
				.property( "name", &Path::getName )
				.property( "points", &Path::getPoints )
				.def( "append", &Path::appendPoint )
				.def( "prepend", &Path::prependPoint )
				.def( "set", &Path::setPoint )
				.def( "remove", &Path::remove )
		];
	}
}
