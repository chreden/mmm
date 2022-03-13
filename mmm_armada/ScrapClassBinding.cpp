#include "ScrapClass_Internal.h"

namespace mmm
{
	void
	scrapclass_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<ScrapClass, TerrainObjectClass, GameObjectClassPtr>( "ScrapClass" )
				.property( "rotationSpeed", &ScrapClass::getRotationSpeed, &ScrapClass::setRotationSpeed )
		];
	}
}