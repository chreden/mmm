#include "ConstructionRig_Internal.h"

namespace mmm
{
	void
	constructionrig_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<ConstructionRig, Producer, EntityPtr>( "ConstructionRig" )
				.property( "constructionObject", &ConstructionRig::getConstructionObject )
				//.property( "numberOfBees", &ConstructionRig::getBeesOnboard, &ConstructionRig::setBeesOnboard )
		];
	}
}
