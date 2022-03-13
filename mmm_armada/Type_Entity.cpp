#include "type_entity.h"
#include "Type_GameObject.h"
#include "MiningStationType.h"
#include "Type_Starbase.h"

namespace mmm
{
	namespace types
	{
		bool
		isEntity( const Entity* const ent )
		{
			return ent && getScriptInterface()->IsValid( ent->m_entity_id );
		}

		bool 
		isExplosion( const Entity* const ent )
		{
			return ent && ent->m_entityType & Type_Explosion;
		}

		bool 
		isFireballExplosion( const Entity* const ent )
		{
			return ent && std::string(typeid(*ent).raw_name()) == ".?AVFireballExplosion@@";
		}
			
		bool 
		isShockwaveExplosion( const Entity* const ent )
		{
			return ent && ent->m_entityType & Type_ShockwaveExplosion;
		}
			
		bool 
		isShockwaveCannon( const Entity* const ent )
		{
			return ent && std::string(typeid(*ent).raw_name()) == ".?AVShockwaveCannon@@";
		}

		bool
		isGameObject( const Entity* const ent )
		{
			return ent && ent->m_entityType & Type_GameObject;
		}

		bool
		isCraft( const Entity* const ent )
		{
			return ent && ent->m_entityType & Type_Craft;
		}

		bool
		isMineArray( const Entity* const ent )
		{
			return ent && 
				   std::string(typeid(*ent).raw_name()) == ".?AVMineArray@@";
		}

		bool
		isCargoShip( const Entity* const ent )
		{
			return ent && ent->m_entityType & Type_CargoShip;
		}

		bool
		isTradingStation( const Entity* const ent )
		{
			return ent &&
				   std::string(typeid(*ent).raw_name()) == ".?AVTradingStation@@";
		}

		bool
		isResearchPod( const Entity* const ent )
		{
			return ent && ent->m_entityType & Type_ResearchPod;
		}

		bool
		isResearchStation( const Entity* const ent )
		{
			return ent && ent->m_entityType & Type_ResearchStation;
		}

		bool
		isColony( const Entity* const ent )
		{
			return ent && std::string(typeid(*ent).raw_name()) == ".?AVColony@@";
		}

		bool 
		isScavenger( const Entity* const ent )
		{
			return ent && ent->m_entityType & Type_Scavenger;
		}

		bool 
		isPlanetMiningBase( const Entity* const ent )
		{
			return ent && std::string(typeid(*ent).raw_name()) == ".?AVPlanetMiningBase@@";
		}

		bool 
		isSensorArray( const Entity* const ent )
		{
			return ent && ent->m_entityType & Type_SensorArray;
		}

		bool
		isPlanet( const Entity* const ent )
		{
			return ent && ent->IsPlanet( );
		}

		bool
		isProducer( const Entity* const ent )
		{
			return ent && ent->m_entityType & Type_Producer;
		}

		bool
		isEvolver( const Entity* const ent )
		{
			return ent && std::string(typeid(*ent).raw_name()) == ".?AVEvolver@@";
		}

		bool
		isFreighter( const Entity* const ent )
		{
			return ent && ent->m_entityType & Type_Freighter;
		}

		bool
		isRepairShip( const Entity* const ent )
		{
			return ent && std::string(typeid(*ent).raw_name()) == ".?AVRepairShip@@";
		}

		bool
		isConstructor( const Entity* const ent )
		{
			return ent && ent->m_entityType & Type_Rig;
		}

		bool
		isMiningStation( const Entity* const ent )
		{
			return ent && ent->m_entityType & Type_MiningStation;
		}

		bool
		isShipyard( const Entity* const ent )
		{
			return ent && ent->m_entityType & Type_Shipyard;
		}

		bool
		isStarbase( const Entity* const ent )
		{
			return ent && ent->m_entityType & Type_Starbase;
		}

		bool
		isAsteroidField( const Entity* const ent )
		{
			return ent && ent->m_entityType & Type_AsteroidField;
		}

		bool 
		isUtritiumBall( const Entity* const ent )
		{
			return ent && std::string(typeid(*ent).raw_name()) == ".?AVUtritiumBall@@";
		}

		bool
		isBackgroundObject( const Entity* const ent )
		{
			return ent && ent->m_entityType & Type_BackgroundObject;
		}

		bool
		isBackgroundPlanet( const Entity* const ent )
		{
			return isBackgroundObject( ent ) &&
					std::string(typeid(*ent).raw_name()) == ".?AVBackgroundPlanet@@";
		}

		bool 
		isLatinumNebula( const Entity* const ent )
		{
			return ent && std::string(typeid(*ent).raw_name()) == ".?AVLatinumNebula@@";
		}

		bool
		isScrap( const Entity* const ent )
		{
			return ent && std::string(typeid(*ent).raw_name()) == ".?AVScrap@@";
		}

		bool
		isTerrainObject( const Entity* const ent )
		{
			//Almost complete - still don't have ultritium ball done, or latinum
			//nebula - need to create one to examine it and see if I can do anything
			//about that.
			return ent && isAsteroidField( ent ) || 
							isBackgroundObject( ent ) ||
							isScrap( ent ) ||
							isUtritiumBall( ent ) ||
							isLatinumNebula( ent ) ||
							isAreaEffectObject( ent );

		}

		bool 
		isAreaEffectObject( const Entity* const ent )
		{
			//Area effect object can be detected by checking for derived types - this is not
			//the best solution but something else can be developed later.
			return isWormhole( ent )  ||
					isNebula( ent )	  ||
					isBlackhole( ent ) ||
					isIonStorm( ent );
		}

		bool 
		isWormhole( const Entity* const ent )
		{
			return ent && (ent->m_entityType & Type_Wormhole);
		}

		bool 
		isNebula( const Entity* const ent )
		{
			return ent && ent->m_entityType & Type_Nebula;
		}

		bool
		isBlackhole( const Entity* const ent )
		{
			return ent && ent->m_entityType & Type_Blackhole;
		}

		bool
		isIonStorm( const Entity* const ent )
		{
			return ent && ent->m_entityType & Type_IonStorm;
		}

		bool
		isResourceContainer( const Entity* const ent )
		{
			if( isGameObject( ent ) )
			{
				return static_cast<const GameObject* const>( ent )->m_pResourceInterface != 0;
			}
			return false;
		}

		bool
		isResourceTransfer( const Entity* const ent )
		{
			if( isMiningStation( ent ) )
			{
				return static_cast<const types::MiningStation* const>( ent )->m_pResourceTransferInterface;
			}
			else if( isStarbase( ent ) )
			{
				return static_cast<const types::Starbase* const>( ent )->m_pResourceTransferInterface;
			}
			return false;
		}

		bool
		isConstructionObject( const Entity* const ent )
		{
			return ent && ent->m_entityType & Type_ConstructionObject;
		}

		bool
		isOrdnance( const Entity* const ent )
		{
			return ent && ent->m_entityType & Type_Ordnance;
		}
			
		bool 
		isBeam( const Entity* const ent )
		{
			return ent && ent->m_entityType & Type_Beam;
		}

		bool
		isPhaser( const Entity* const ent )
		{
			return ent && std::string(typeid(*ent).raw_name()) == ".?AVPhaser@@";
		}

		bool 
		isMissile( const Entity* const ent )
		{
			return ent && ent->m_entityType & Type_Missile;
		}

		bool
		isPhotonTorpedo( const Entity* const ent )
		{
			return ent && std::string(typeid(*ent).raw_name()) == ".?AVPhotonTorpedo@@";
		}

		bool 
		isMine( const Entity* const ent )
		{
			return ent && ent->m_entityType & Type_Mine;
		}

		bool 
		isGravityMine( const Entity* const ent )
		{
			return ent && std::string(typeid(*ent).raw_name()) == ".?AVGravityMine@@";
		}

		bool 
		isAntimatterMine( const Entity* const ent )
		{
			return ent && std::string(typeid(*ent).raw_name()) == ".?AVAntiMatterMine@@";
		}

		bool 
		isBeamToggle( const Entity* const ent )
		{
			return ent && ent->m_entityType & Type_BeamToggle;
		}

		bool 
		isBullet( const Entity* const ent )
		{
			return ent && ent->m_entityType & Type_Bullet;
		}

		bool 
		isArtillery( const Entity* const ent )
		{
			return ent && std::string(typeid(*ent).raw_name()) == ".?AVArtillery@@";
		}

		bool
		isPulsePhaser( const Entity* const ent )
		{
			return ent && std::string(typeid(*ent).raw_name()) == ".?AVPulsePhaser@@";
		}
	}
}