#include "Craft_Internal.h"

namespace mmm
{
	void
	craft_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<Craft, GameObject, EntityPtr>( "Craft" )
				.property( "name", &Craft::getName, &Craft::setName )
				.property( "shields", &Craft::getShields, &Craft::setShields )
				.property( "impulseSpeed", &Craft::getImpulseSpeed, &Craft::setImpulseSpeed )
				.property( "alert", &Craft::getAlertStatus, &Craft::setAlertStatus )
				.property( "movementAutonomy", &Craft::getMovementAutonomy, &Craft::setMovementAutonomy )
				.property( "specialWeaponAutonomy", &Craft::getSpecialWeaponAutonomy, &Craft::setSpecialWeaponAutonomy )
				.property( "maxShields", &Craft::getMaxShields, &Craft::setMaxShields )
				.property( "shieldsValue", &Craft::getShieldsValue, &Craft::setShieldsValue )
				.property( "crew", &Craft::getCrew, &Craft::setCrew )
				.property( "maxCrew", &Craft::getMaxCrew, &Craft::setMaxCrew )
				.property( "systems", &Craft::getSystems )
				.def( "explode", &Craft::explode )
				.scope
				[
					class_<eAlertStatus>("AlertState")
						.enum_("constants")
						[
							value("Red", ALERT_STATUS_RED ),
							value("Yellow", ALERT_STATUS_YELLOW),
							value("Green", ALERT_STATUS_GREEN)
						],
					class_<eMovementAutonomy>("MovementAutonomy")
						.enum_("constants")
						[
							value("Low", MOVEMENT_AUTONOMY_LOW),
							value("Medium", MOVEMENT_AUTONOMY_MED),
							value("High", MOVEMENT_AUTONOMY_HIGH)
						],
					class_<eSpecialWeaponAutonomy>("WeaponAutonomy")
						.enum_("constants")
						[
							value("None", SPECIAL_WEAPON_AUTONOMY_NONE),
							value("Medium", SPECIAL_WEAPON_AUTONOMY_MED),
							value("High", SPECIAL_WEAPON_AUTONOMY_HIGH)
						],
					class_<eCraftSystem>("System")
						.enum_("constants")
						[
							value("Engines", Engines),
							value("LifeSupport", LifeSupport),
							value("Shields", Shields),
							value("Weapons", Weapons),
							value("Sensors", Sensors)
						]
				]
		];
	}
}
