#include "Save_Internal.h"

namespace mmm
{
	namespace 
	{
		//Static instance of the object so that we can use
		//properties on it. Is stored the the luabind globals
		//table.
		Save save;
	}

	void
	save_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<Save>("SaveData")
				.def( "save", &Save::doSave )
				.def( "write", (bool (Save::*)(const std::string&)) &Save::write )
				.def( "write", (bool (Save::*)(float)) &Save::write )
				.def( "write", (bool (Save::*)(bool)) &Save::write )
				.property( "position", &Save::getLength, &Save::setWrite )
		];

		globals(state)["Save"] = &save;
	}
}
