#include "IonStorm_Internal.h"

namespace mmm
{
	void
	ionstorm_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<IonStorm, AreaEffectObject, EntityPtr>( "IonStorm" )
				.property( "state", &IonStorm::getState )
				.property( "timeLeft", &IonStorm::getTimeLeft, &IonStorm::setTimeLeft )
				.scope
				[
					class_<types::IonStorm::StormState>("State")
						.enum_("constants")
						[
							value("Closed", types::IonStorm::Closed),
							value("Closing", types::IonStorm::Closing),
							value("Open", types::IonStorm::Open),
							value("Opening", types::IonStorm::Opening)
						]
				]
		];
	}
}
