#include "OrdnanceDamage.h"

namespace mmm
{
	void
	ordnancedamage_register( lua_State* state )
	{
		using namespace luabind;
		module(state)
		[
			class_<OrdnanceDamage, OrdnanceDamagePtr>( "OrdnanceDamage" )
				.property( "total", &OrdnanceDamage::getTotal, &OrdnanceDamage::setTotal )
				.property( "flags", &OrdnanceDamage::getFlags, &OrdnanceDamage::setFlags )
				.scope
				[
					class_<Special>( "DamageFlags" )
						.enum_("constants")
						[
							value("Standard", Standard ),
							value("StandardIgnoreShield", StandardIgnoreShield ),
							value("IgnoreShield", IgnoreShield),
							value("DisableEngines", DisableEngines),
							value("DisableLifesupport", DisableLifesupport),
							value("DisableWeapons", DisableWeapons),
							value("DisableShields", DisableShields),
							value("DisableSensors", DisableSensors),
							value("DamageShieldsOnly", DamageShieldsOnly)
						]
				]
		];
	}
}
