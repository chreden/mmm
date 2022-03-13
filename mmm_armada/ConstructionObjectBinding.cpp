#include "ConstructionObject_Internal.h"
#include "CraftClass_Internal.h"

namespace mmm
{
	void
	constructionobject_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<ConstructionObject, GameObject, EntityPtr>( "ConstructionObject" )
				.property("builder", &ConstructionObject::getBuilder )
				.property("buildClass", &ConstructionObject::getBuildClass )
		];
	}
}
