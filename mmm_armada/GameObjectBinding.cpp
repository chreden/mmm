#include "GameObject_Internal.h"
#include "GameObjectClass_Internal.h"
#include "Team_Internal.h"
#include "Race_Internal.h"
#include "Path_Internal.h"

namespace mmm
{
	void
	gameobject_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<GameObject, bases<Entity, ResourceInterface>, EntityPtr>( "GameObject" )
				.property( "odf", &GameObject::getOdf )
				.property( "hull", &GameObject::getHealth, &GameObject::setHealth )
				.property( "hullValue", &GameObject::getHitpoints, &GameObject::setHitpoints )
				.property( "maxHull", &GameObject::getMaximumHealth, &GameObject::setMaximumHealth )
				.property( "specialEnergy", &GameObject::getSpecialEnergy, &GameObject::setSpecialEnergy )
				.property( "maxSpecialEnergy", &GameObject::getMaxSpecialEnergy, &GameObject::setMaxSpecialEnergy )
				.property( "specialEnergyValue", &GameObject::getSpecialEnergyValue, &GameObject::setSpecialEnergyValue )
				.property( "label", &GameObject::getHandle )
				.property( "invincible", &GameObject::getInvincible, &GameObject::setInvincible )
				.property( "velocity", &GameObject::getVelocity, &GameObject::setVelocity )
				.property( "forceOntoMap", &GameObject::getForceOntoMap, &GameObject::setForceOntoMap )
				.property( "underAttack", &GameObject::isUnderAttack )
				.property( "cloaked", &GameObject::isCloaked )
				.property( "destroyed", &GameObject::isDestroyed )
				.property( "canCloak", &GameObject::canCloak )
				.property( "player", &GameObject::getTeam, &GameObject::setTeam )
				.property( "perceivedTeam", &GameObject::getPerceivedTeam, &GameObject::setPerceivedTeam )
				.property( "aiControlled", &GameObject::isAiControlled )
				.property( "class", &GameObject::getClass )
				.property( "race", &GameObject::getRace )
				.property("alpha", &GameObject::getAlpha, &GameObject::setAlpha)
				.property("omega", &GameObject::getOmega, &GameObject::setOmega)
				.property("accel", &GameObject::getAccel, &GameObject::setAccel)
				.def( "cloak", &GameObject::cloak )
				.def( "decloak", &GameObject::decloak )
				.def( "immediateCloak", &GameObject::immediateCloak )
				.def( "giveOrder", (void (GameObject::*)(AiCommand, const Vector3&)) &GameObject::giveOrder )
				.def( "giveOrder", (void (GameObject::*)(AiCommand, EntityPtr)) &GameObject::giveOrder )
				.def( "giveOrder", (void (GameObject::*)(AiCommand, const std::string&, const Vector3&)) &GameObject::giveOrder )
				.def( "giveOrder", (void (GameObject::*)(AiCommand, const Path&)) &GameObject::giveOrder )
				.def( "giveOrder", (void (GameObject::*)(AiCommand, long)) &GameObject::giveOrder )
				.def( "giveOrder", (void (GameObject::*)(AiCommand)) &GameObject::giveOrder )
				.def( "addWeapon", &GameObject::addWeapon )
				.scope
				[
					class_<AiCommand>("Order")
						.enum_("constants")
						[
							value( "None", CMD_NONE ),
							value( "Default", CMD_DEFAULT ),
							value( "Select", CMD_SELECT ),
							value( "Stop", CMD_STOP ),
							value( "Go", CMD_GO ),						
							value( "GoSingle", CMD_GO_SINGLE ),				
							value( "Attack", CMD_ATTACK ),					//Done
							value( "SpecialAttack", CMD_SPECIAL_ATTACK ),			
							value( "AnchoredAttack", CMD_ANCHORED_ATTACK ),
							value( "TransportAttack", CMD_TRANSPORT_ATTACK ),
							value( "Queue", CMD_QUEUE ),
							value( "Follow", CMD_FOLLOW ),
							value( "Formation", CMD_FORMATION ),
							value( "Transport", CMD_TRANSPORT ),	
							value( "TransportSpecial", CMD_TRANSPORT_SPECIAL ),
							value( "Recrew", CMD_RECREW ),					//Done
							value( "SetRallyPoint", CMD_SET_RALLY_POINT ),
							value( "Repair", CMD_GET_REPAIR ),				//Done
							value( "Defend", CMD_DEFEND ),
							value( "CancelBuild", CMD_CANCEL_BUILD ),
							value( "Decommision", CMD_DECOMMISSION ),			//Done
							value( "Mine", CMD_MINE ),
							value( "SearchAndDestroy", CMD_SEARCH_AND_DESTROY ),		//Done
							value( "Guard", CMD_GUARD ),	
							value( "Scout", CMD_SCOUT ),					//Done
							value( "Build", CMD_BUILD ),					//Done
							value( "Patrol", CMD_PATROL ),					//Doneish
							value( "RedAlert", CMD_RED_ALERT ),
							value( "YellowAlert", CMD_YELLOW_ALERT ),
							value( "GreenAlert", CMD_GREEN_ALERT ),
							value( "CancelBuildQueueItem", CMD_CANCEL_BUILD_QUEUE_ITEM ),
							value( "Wormhole", CMD_WORMHOLE ),
							value( "FormFormation", CMD_FORMFORMATION ),
							value( "GoRally", CMD_GORALLY ),
							value( "StartTrade", CMD_START_TRADE ),
							value( "EndTrade", CMD_END_TRADE ),
							value( "Trading", CMD_TRADING ),
							value( "GiveResource", CMD_GIVERESOURCE ),
							value( "Colonize", CMD_COLONIZE ),
							value( "RepairOther", CMD_REPAIR_OTHER ),
							value( "BuyResource", CMD_BUY_RESOURCE ),
							value( "SellResource", CMD_SELL_RESOURCE ),
							value( "SetFormation", CMD_SET_FORMATION ),
							value( "GoWarp", CMD_GO_WARP ),
							value( "GoWarpSingle", CMD_GO_WARP_SINGLE ),
							value( "SetAttackMode", CMD_SET_ATTACK_MODE ),
							value( "SpecialWeaponNone", CMD_SPECIAL_WEAPON_AUTONOMY_NONE ),
							value( "SpecialWeaponMedium", CMD_SPECIAL_WEAPON_AUTONOMY_MED ),
							value( "SpecialWeaponHigh", CMD_SPECIAL_WEAPON_AUTONOMY_HIGH ),
							value( "MoveLow", CMD_MOVE_LOW ),
							value( "MoveMedium", CMD_MOVE_MED ),
							value( "MoveHigh", CMD_MOVE_HIGH ),
							value( "WeaponQueue", CMD_WEAPON_QUEUE ),
							value( "GetSuperRepair", CMD_GET_SUPER_REPAIR ),
							value( "SetFormationOrientation", CMD_SET_FORMATION_ORIENTATION ),
							value( "RecycleMetal", CMD_RECYCLE_METAL ),
							value( "RecycleDilithium", CMD_RECYCLE_DILITHIUM )
						]
				]
		];
	}
}
