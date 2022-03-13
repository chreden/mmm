#include "Entity_Internal.h"
#include "Type_Entity.h"
#include "BeamToggle.h"

#include "Team_Internal.h"

#include "Explosion_Internal.h"
#include "ConstructionObject_Internal.h"
#include "CraftSystem_Internal.h"
#include "Freighter_Internal.h"
#include "RepairShip_Internal.h"
#include "Colony_Internal.h"
#include "Evolver_Internal.h"
#include "ConstructionRig_Internal.h"
#include "BackgroundObject_Internal.h"
#include "BackgroundPlanet_Internal.h"
#include "BlackHole_Internal.h"
#include "ResearchPod_Internal.h"
#include "CargoShip_Internal.h"
#include "AsteroidField.h"
#include "Scavenger.h"
#include "PlanetMiningBase.h"
#include "SensorArray.h"
#include "MineArray.h"

	#include "MiningStation.h"
	#include "Planet_Internal.h"
	#include "ResourceTransferInterface.h"
		#include "Starbase_Internal.h"

	#include "IonStorm_Internal.h"
	#include "Nebula_Internal.h"
	#include "Wormhole.h"
	#include "Scrap_Internal.h"
	#include "UtritiumBall_Internal.h"
	#include "LatinumNebula_Internal.h"

#include "PulsePhaser_Internal.h"
#include "Phaser_Internal.h"
#include "PhotonTorpedo_Internal.h"
#include "Artillery.h"
#include "ResearchStation.h"

#include "ResourceInterface_Internal.h"

#include "TradingStation.h"

#include "Mine.h"
#include "AntimatterMine.h"
#include "GravityMine.h"

namespace mmm
{
	namespace
	{
		const std::size_t Address_GetPosition	= 0x004cfd90;
		const std::size_t Address_GetScale		= 0x004cff40;
		const std::size_t Address_SetScale		= 0x004cff20;
		const std::size_t Address_EnableScaling	= 0x004cff50;
		const std::size_t Address_CanTeamSee		= 0x004d0090;
	}

	const Vector3 VectorUndefined( 0, 0, 0 );

	EntityPtr
	Entity::create( types::Entity* entity )
	{
		return EntityPtr( new Entity( entity ) );
	}

	Entity::Entity( types::Entity* ent )
		: entityReference_( EntityReference::create(ent) )
	{

	}

	bool 
	Entity::operator==( EntityPtr entity ) const
	{
		return entity && 
			   getEntity() == entity->getEntity();
	}

	types::Entity* 
	Entity::getEntity() const
	{
		return entityReference_->getEntity();
	}

	const Vector3
	Entity::getScale( ) const
	{
		if( getEntity() )
		{
			return (getEntity()->*memory_function<const Vector3& (types::Entity::*)( ) const>( Address_GetScale ))();
		}
		return VectorUndefined;
	}

	const Vector3
	Entity::getPosition( ) const
	{
		if( getEntity() )
		{
			typedef const Vector3& (types::Entity::*MemFunction)( ) const;
			MemFunction function = memory_function< MemFunction >( Address_GetPosition );
			return (getEntity()->*function)( );
		}
		return VectorUndefined;
	}

	int 
	Entity::getID( ) const
	{
		if( getEntity() )
		{
			return getEntity()->m_entity_id;
		}
		return 0;
	}

	bool 
	Entity::canTeamSee( const Team& team ) const
	{
		if( getEntity() )
		{
			return getEntity()->m_isVisible & ( 1 << team.getNumber() );		
		}
		return false;
	}

	void 
	Entity::setScale( const Vector3& scale )
	{
		if( getEntity() )
		{
			(getEntity()->*memory_function< void (types::Entity::*)( bool ) >( Address_EnableScaling ))
				( true );
			(getEntity()->*memory_function< void (types::Entity::*)( const Vector3& ) >( Address_SetScale ))
				( scale );
		}
	}

	void 
	Entity::setPosition( const Vector3& pos )
	{
		if( getEntity() )
		{
			getEntity()->SetOrigin( pos );
			if( types::isGameObject( getEntity() ) )
			{
				types::GameObject* object = static_cast<types::GameObject*>( getEntity() );
				object->m_position = pos;
			}
		}
	}

	const Vector3
	Entity::getForward( ) const
	{
		return getEntity()->GetTransform().forward;
	}

	void		   
	Entity::setForward( const Vector3& fv )
	{
		if( getEntity() )
		{
			getEntity()->SetForward( fv );
		}
	}

	void
	Entity::replace( const std::string& odf )
	{
		if( getEntity() )
		{
			entityReference_ = EntityReference::create( GetEntity<types::Entity>(
				getScriptInterface( )->ReplaceObject( getID(), const_cast<char*>( odf.c_str( ) ) ) ) );
			doReplace( );
		}
	}

	void 
	Entity::setHide( bool value )
	{
		getEntity()->m_disable_render = value;
	}

		
	bool
	Entity::getHide( ) const
	{
		return getEntity()->m_disable_render;
	}

	bool		   
	Entity::empty( ) const
	{
		return getEntity() == nullptr;
	}

	bool
	Entity::expired( ) const
	{
		return getEntity() && getEntity()->m_expired;
	}

	bool
	Entity::doReplace( ) const
	{
		using namespace luabind;
		using namespace luabind::detail;

		EntityPtr newEntity( createEntityPtr(getEntity()) );
		if( !newEntity )
		{
			return false;
		}

		if( typeid(*this) !=
			typeid(*newEntity.get()) )
		{
			lua_State* state = common::Storage::instance().mainLuaVM;

			object_rep* obj = touserdata<object_rep>( handle( state, 1 ) );

			void* oldstorage = obj->get_instance( registered_class<Entity>::id ).first;
			obj->deallocate( oldstorage );
	
			newEntity->allocateReplacement( obj );

			obj->m_classrep->get_table(state);
			lua_setfenv(state, 1);
			lua_rawgeti(state, LUA_REGISTRYINDEX, obj->m_classrep->metatable_ref());
			lua_setmetatable(state, 1);
		}
		return true;
	}

	bool		   
	Entity::isValid() const
	{
		return doReplace();
	}

	void
	Entity::allocateReplacement( luabind::detail::object_rep* obj )
	{
		entity_allocate_replacement<Entity>( obj, shared_from_this() );	
	}

	bool
	Entity::isType( eEntityType type ) const
	{
		types::Entity* ent = getEntity();

		switch( type )
		{
		case Entity_Entity:
			return true;
			break;
		case Entity_GameObject:
			return types::isGameObject( ent );
			break;
		case Entity_ConstructionObject:
			return types::isConstructionObject( ent );
			break;
		case Entity_Craft:
			return types::isCraft( ent ); 
			break;
		case Entity_PlanetMiningBase:
			return types::isCraft( ent ) &&
				   types::isPlanetMiningBase( ent );
			break;
		case Entity_CargoShip:
			return types::isCargoShip( ent );
			break;
		case Entity_SensorArray:
			return types::isSensorArray( ent );
			break;
		case Entity_MineArray:
			return types::isCraft( ent ) &&
				   types::isMineArray( ent );
			break;
		case Entity_Scavenger:
			return types::isScavenger( ent );
			break;
		case Entity_ResearchStation:
			return types::isResearchStation( ent );
			break;
		case Entity_ResearchPod:
			return types::isResearchPod( ent );
			break;
		case Entity_Colony:
			return types::isCraft( ent ) &&
					types::isColony( ent );
			break;
		case Entity_Planet:
			return types::isPlanet( ent );
			break;
		case Entity_Producer:
			return types::isProducer( ent );
			break;
		case Entity_ResourceContainer:
			return types::isResourceContainer( ent );
			break;
		case Entity_BackgroundObject:
			return types::isBackgroundObject( ent );
			break;
		case Entity_BackgroundPlanet:
			return types::isBackgroundPlanet( ent );
			break;
		case Entity_RepairShip:
			return types::isRepairShip( ent );
			break;
		case Entity_Freighter:
			return types::isFreighter( ent );
			break;
		case Entity_Evolver:
			return types::isProducer( ent ) && 
					types::isEvolver( ent );
			break;
		case Entity_BlackHole:
			return types::isBlackhole( ent );
			break;
		case Entity_Constructor:
			return types::isConstructor( ent );
			break;
		case Entity_Starbase:
			return types::isStarbase( ent );
			break;
		case Entity_MiningStation:
			return types::isMiningStation( ent );
			break;
		case Entity_TradingStation:
			return types::isMiningStation(ent) &&
				   types::isTradingStation( ent );
			break;
		case Entity_Wormhole:
			return types::isWormhole( ent );
			break;
		case Entity_LatinumNebula:
			return types::isLatinumNebula( ent );
			break;
		case Entity_TerrainObject:
			return types::isTerrainObject( ent );
			break;
		case Entity_AsteroidField:
			return types::isAsteroidField( ent );
			break;
		case Entity_UtritiumBall:
			return types::isUtritiumBall( ent );
			break;
		case Entity_Scrap:
			return types::isTerrainObject(ent) &&
					types::isScrap( ent );
			break;
		case Entity_AreaEffectObject:
			return types::isAreaEffectObject( ent );
			break;
		case Entity_Nebula:
			return types::isNebula( ent );
			break;
		case Entity_Shipyard:
			return types::isShipyard( ent );
			break;
		case Entity_IonStorm:
			return types::isIonStorm( ent );
			break;
		case Entity_Ordnance:
			return types::isOrdnance( ent );
			break;
		case Entity_Beam:
			return types::isBeam( ent );
			break;
			case Entity_Phaser:
				return types::isBeam( ent ) &&
							types::isPhaser( ent );
				break;
		case Entity_BeamToggle:
			return types::isBeamToggle( ent );
			break;
		case Entity_Missile:
			return types::isMissile( ent );
			break;
			case Entity_PhotonTorpedo:
				return types::isMissile( ent ) &&
					   types::isPhotonTorpedo( ent );
				break;
		case Entity_Bullet:
			return types::isBullet( ent );
			break;
			case Entity_Artillery:
				return types::isBullet( ent ) &&
					   types::isArtillery( ent );
			case Entity_PulsePhaser:
				return types::isBullet( ent ) &&
					   types::isPulsePhaser( ent );
				break;
		case Entity_Mine:
			return types::isMine(ent);
			break;
			case Entity_GravityMine:
				return types::isMine(ent) &&
					   types::isGravityMine( ent );
				break;
			case Entity_AntimatterMine:
				return types::isMine(ent) &&
					   types::isAntimatterMine( ent );
				break;
		case Entity_Explosion:
			return types::isExplosion(ent);
			break;
		case Entity_ResourceTransferInterface:
			return types::isResourceTransfer( ent );
			break;
		}

		return false;
	}


	EntityPtr 
	createEntityPtr( types::Entity* ent )
	{
		if( !ent )
		{
			return EntityPtr();
		}

		//In order to spawn the correct type of entity, we must actually find out what the thing is.
		//We then call the function dependent on this.
		if( isGameObject( ent ) )
		{
			if( isTerrainObject( ent ) )
			{
				if( isAreaEffectObject( ent ) )
				{
					if( isWormhole( ent ) )
					{
						return Wormhole::create( ent );
					}
					else if( isNebula( ent ) )
					{
						return Nebula::create( ent );
					}
					else if( isIonStorm( ent ) )
					{
						return IonStorm::create( ent );
					}
					else if( isBlackhole( ent ) )
					{
						return BlackHole::create( ent );
					}
					return AreaEffectObject::create( ent );
				}
				if( isScrap( ent ) )
				{
					return Scrap::create( ent );
				}
				else if( isUtritiumBall( ent ) )
				{
					return UtritiumBall::create( ent );
				}
				else if( isBackgroundObject( ent ) )
				{
					if( isBackgroundPlanet( ent ) )
					{
						return BackgroundPlanet::create( ent );
					}
					return BackgroundObject::create( ent );
				}
				else if( isLatinumNebula( ent ) )
				{
					return LatinumNebula::create( ent );
				}
				else if( isAsteroidField( ent ) )
				{
					return AsteroidField::create( ent );
				}
				return TerrainObject::create( ent );
			}
			else if( isCraft( ent ) )
			{
				if( isProducer( ent ) )
				{
					if( isPlanet( ent ) )
					{
						return Planet::create( ent );
					}
					else if( isMiningStation( ent ) )
					{
						if( isTradingStation( ent ) )
						{
							return TradingStation::create( ent );
						}
						return MiningStation::create( ent );
					}
					else if( isShipyard( ent ) )
					{
						if( isStarbase( ent ) )
						{
							return Starbase::create( ent );
						}
						return Shipyard::create( ent );
					}
					else if( isEvolver( ent ) )
					{
						return Evolver::create( ent );
					}
					else if( isConstructor( ent ) )
					{
						return ConstructionRig::create( ent );
					}
					else if( isResearchStation( ent ) )
					{
						return ResearchStation::create( ent );
					}
					return Producer::create( ent );
				}
				else if( isFreighter( ent ) )
				{
					return Freighter::create( ent );
				}
				else if( isRepairShip( ent ) )
				{
					return RepairShip::create( ent );
				}
				else if( isColony( ent ) )
				{
					return Colony::create( ent );
				}
				else if( isResearchPod( ent ) )
				{
					return ResearchPod::create( ent );
				}
				else if( isCargoShip( ent ) )
				{
					return CargoShip::create( ent );
				}
				else if( isScavenger( ent ) )
				{
					return Scavenger::create( ent );
				}
				else if( isPlanetMiningBase( ent ) )
				{
					return PlanetMiningBase::create( ent );
				}
				else if( isSensorArray( ent ) )
				{
					return SensorArray::create( ent );
				}
				else if( isMineArray( ent ) )
				{
					return MineArray::create( ent );
				}
				return Craft::create( ent );
			}
			else if( isConstructionObject( ent ) )
			{
				return ConstructionObject::create( ent );
			}

			return GameObject::create( ent );
		}
		else if( isOrdnance( ent ) )
		{
			if( isMissile( ent ) )
			{
				//chainpulsar
				//klingoncommandoteam
				//colonizerpod
				//shieldremovingtorpedo
				//computeroverride
				//polarontorpedo
				//manheimeffect
				//myorton
				//plasmacannon

				if( isPhotonTorpedo( ent ) )
				{
					return PhotonTorpedo::create( ent );
				}
				
				return Missile::create( ent );
			}
			else if( isMine( ent ) )
			{
				if( isGravityMine( ent ) )
				{
					return GravityMine::create( ent );
				}
				else if ( isAntimatterMine( ent ) )
				{
					return AntimatterMine::create( ent );
				}
				return Mine::create( ent );
			}
			else if( isBeam( ent ) )
			{
				//transientrift
				//warpcoreoverload
				//clairvoyantlink
				//psionicinsanity
				//physconicblast
				//hologenerator
				//romulanspy
				//fedshieldemitter
				//containmentbreach
				//shieldgendisruptor
				//borgenergyemitter
				//miningbeam
				//borgbore
				//holoemitter
				//shieldremodulation
				//plasmaoverdrive
				//psionicdisruption
				//colonizingbem
				//utritiumbeam

				if( isPhaser( ent ) )
				{
					return Phaser::create( ent );
				}
				return Beam::create( ent );
			}
			else if( isBeamToggle( ent ) )
			{
				//techassimbeam
				//shielddisruptor
				//energyshiedlconverter
				//resourcextractionbeam
				//tractorbeam
				//shieldinversion
				//holdingbeam
				//accelcannon
				return BeamToggle::create( ent );
			}
			else if( isBullet( ent ) )
			{
				//nanites
				//shieldharmonic
				//probetorpedo
				//ionstormtorpedo
				//microorganism
				//transwarpdrive
				//nebulaflux
				//repulsionfield
				//targetoverride

				if( isArtillery( ent ) )
				{
					return Artillery::create( ent );
				}
				else if( isPulsePhaser( ent ) )
				{
					return PulsePhaser::create( ent );
				}
				return Bullet::create( ent );
			}
			return Ordnance::create( ent );
		}
		else if( isExplosion( ent ) )
		{
			//FireballExplosion
				//Omega explosion?
			//ShockwaveExplosion
				//ShockwaveCannon
			return Explosion::create( ent );
		}
		
		return Entity::create( ent );
	}

	bool
	Entity::hook( const std::string& id, EntityHook::Type type, luabind::object table, luabind::object function, luabind::object argument )
	{
		return entityReference_->addHook( id, type, table, function, argument );
	}

	bool
	Entity::unhook( const std::string& id )
	{
		return entityReference_->unhook( id );
	}

	bool
	Entity::unhook( HookPtr hook )
	{
		return entityReference_->unhook( hook );
	}

	luabind::object
	Entity::getHooks( ) const
	{
		return entityReference_->getHooks( );
	}
}
