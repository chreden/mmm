#pragma once

namespace mmm
{
	namespace types
	{
		struct Entity
		{
			const static int NO_ENTITY;
			void* m_instance;
			unsigned long m_isVisible;	//Bitflag.
			unsigned long m_wasVisible;
			unsigned long m_seen;
			unsigned long m_entityType;
			ST3D_Colour m_light_colour;
			bool m_light_source_enabled;
			bool m_was_drawn;
			bool m_disable_render;
			bool m_expired;
			int m_entity_id;
			static std::list<Entity*> g_entityList;

			virtual ~Entity( ) = 0;
			virtual void DoExpire( ) = 0;
			virtual bool CanUserSee( ) = 0;

			virtual bool IsPlanet( ) const = 0; //Not really const but I care not
			virtual bool IsEvolver( ) = 0;
			virtual bool IsTradingStation( ) = 0;
			virtual bool IsMineArray( ) = 0;
			virtual void GetBoundingBox( ) = 0; //Wrong return type.
			virtual void SetOrigin( const Vector3& point ) = 0;
			virtual void SetTransform( ) = 0; //Wrong param
			virtual void SetForward( const Vector3& point ) = 0;
			virtual const Matrix34 & GetTransform() const = 0;
			virtual void Render( void* camera ) = 0;
		};

		bool isResourceTransfer( const Entity* const ent );
		bool isEntity( const Entity* const ent );
			bool isExplosion( const Entity* const ent );
				bool isFireballExplosion( const Entity* const ent );
				bool isShockwaveExplosion( const Entity* const ent );
					bool isShockwaveCannon( const Entity* const ent );
					//omega
			bool isResourceContainer( const Entity* const ent );
			bool isGameObject( const Entity* const ent );
				bool isCraft( const Entity* const ent );
					bool isCargoShip( const Entity* const ent );
					bool isColony( const Entity* const ent );
					bool isScavenger( const Entity* const ent );
					bool isPlanetMiningBase( const Entity* const ent );
					bool isSensorArray( const Entity* const ent );
					bool isMineArray( const Entity* const ent );
					bool isProducer( const Entity* const ent );
						bool isPlanet( const Entity* const ent );
						bool isConstructor( const Entity* const ent );
						bool isEvolver( const Entity* const ent );
						bool isResearchStation( const Entity* const ent );
						bool isShipyard( const Entity* const ent );
							bool isStarbase( const Entity* const ent );
						bool isMiningStation( const Entity* const ent );
							bool isTradingStation( const Entity* const ent );
					bool isFreighter( const Entity* const ent );			
					bool isRepairShip( const Entity* const ent );
					bool isResearchPod( const Entity* const ent );
				bool isTerrainObject( const Entity* const ent );
					bool isScrap( const Entity* const ent );
					bool isAsteroidField( const Entity* const ent );
					bool isLatinumNebula( const Entity* const ent );
					bool isBackgroundObject( const Entity* const ent );
						bool isBackgroundPlanet( const Entity* const ent );
					bool isUtritiumBall( const Entity* const ent );
					bool isAreaEffectObject( const Entity* const ent );
						bool isWormhole( const Entity* const ent );
						bool isNebula( const Entity* const entity );
						bool isBlackhole( const Entity* const entity );
						bool isIonStorm( const Entity* const entity );
				bool isConstructionObject( const Entity* const ent );
			bool isOrdnance( const Entity* const entity );
				bool isMissile( const Entity* const ent );
					bool isPhotonTorpedo( const Entity* const ent );
				bool isMine( const Entity* const ent );
					bool isGravityMine( const Entity* const ent );
					bool isAntimatterMine( const Entity* const ent );
				bool isBeam( const Entity* const ent );
					bool isPhaser( const Entity* const ent );
				bool isBeamToggle( const Entity* const ent );
				bool isBullet( const Entity* const ent );
					bool isArtillery( const Entity* const ent );
					bool isPulsePhaser( const Entity* const ent );
	}
}
