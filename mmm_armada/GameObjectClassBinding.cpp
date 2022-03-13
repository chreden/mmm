#include "GameObjectClass_Internal.h"

namespace mmm
{
	void
	gameobjectclass_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<GameObjectClass, GameObjectClassPtr>("GameObjectClass")
				.property("label", &GameObjectClass::getLabel)
				//.property("maxSpecialEnergy", &GameObjectClass::getMaxSpecialEnergy, &GameObjectClass::setMaxSpecialEnergy )
				.property("name", &GameObjectClass::getUnitString, &GameObjectClass::setUnitString )
				.property("odf", &GameObjectClass::getODF )
		];
	}
}