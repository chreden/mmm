#include "Entity_Internal.h"
#include "Entities_Internal.h"
#include "Team_Internal.h"

namespace mmm
{
	void
	entity_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<Entity, EntityPtr>( "Entity" )
				.property( "position", &Entity::getPosition, &Entity::setPosition )
				.property( "scale", &Entity::getScale, &Entity::setScale )
				.property( "hide", &Entity::getHide, &Entity::setHide )
				.property( "forward", &Entity::getForward, &Entity::setForward )
				.property( "id", &Entity::getID )
				.property( "valid", &Entity::isValid )
				.property( "hooks", &Entity::getHooks )
				.property( "type", &Entity::getType )
				.def( "isType", &Entity::isType )
				.def( "canPlayerSee", &Entity::canTeamSee )
				.def( "replace", &Entity::replace )
				.def( "hook", &Entity::hook )
				.def( "unhook", (bool (Entity::*)(const std::string&))&Entity::unhook)
				.def( "unhook", (bool (Entity::*)(HookPtr))&Entity::unhook)
				.def( self == other<EntityPtr>())
				.scope
				[
					def("add", (EntityPtr (*)(const std::string&, int, const Vector3&))&Entities::add),
					def("add", (EntityPtr (*)(const std::string&, TeamPtr, const Vector3&))&Entities::add),
					def("remove", &Entities::remove),
					class_<EntityType>("Type")
						.enum_("constants")
						[
							value("Entity", Entity_Entity),
								value("GameObject", Entity_GameObject),
									value("Craft", Entity_Craft),
										value("CargoShip", Entity_CargoShip),
										value("Colony", Entity_Colony ),
										value("Freighter", Entity_Freighter),
										value("RepairShip", Entity_RepairShip),
										value("ResearchPod", Entity_ResearchPod),
										value("Scavenger", Entity_Scavenger),
										value("PlanetMiningBase", Entity_PlanetMiningBase),
										value("SensorArray", Entity_SensorArray),
										value("MineArray", Entity_MineArray),
										value("Producer", Entity_Producer),
											value("Evolver", Entity_Evolver ),			
											value("Planet", Entity_Planet),
											value("ConstructionRig", Entity_Constructor),
											value("ResearchStation", Entity_ResearchStation),
											value("Shipyard", Entity_Shipyard),
												value("Starbase", Entity_Starbase),
											value("MiningStation", Entity_MiningStation),
												value("TradingStation", Entity_TradingStation),
									value("TerrainObject", Entity_TerrainObject),
										value("AsteroidField", Entity_AsteroidField),
										value("Scrap", Entity_Scrap),
										value("LatinumNebula", Entity_LatinumNebula),
										value("BackgroundObject", Entity_BackgroundObject),
											value("BackgroundPlanet", Entity_BackgroundPlanet),
										value("UtritiumBall", Entity_UtritiumBall),
										value("AreaEffectObject", Entity_AreaEffectObject),
											value("Wormhole", Entity_Wormhole),
											value("Nebula", Entity_Nebula),
											value("IonStorm", Entity_IonStorm),
											value("BlackHole", Entity_BlackHole),
									value("ConstructionObject", Entity_ConstructionObject),
								value("Ordnance", Entity_Ordnance),
									value("Beam", Entity_Beam),
										value("Phaser", Entity_Phaser),
									value("BeamToggle", Entity_BeamToggle),
									value("Missile", Entity_Missile),
										value("PhotonTorpedo", Entity_PhotonTorpedo),
									value("Bullet", Entity_Bullet),
										value("Artillery", Entity_Artillery),
										value("PulsePhaser", Entity_PulsePhaser),
									value("Mine", Entity_Mine),
										value("AntimatterMine", Entity_AntimatterMine),
										value("GravityMine", Entity_GravityMine),
								value("Explosion", Entity_Explosion),
							value("ResourceInterface", Entity_ResourceContainer),
							value("ResourceTransferInterface", Entity_ResourceTransferInterface)
						]
				]
		];
	}
}
