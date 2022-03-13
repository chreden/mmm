#include "Type_GameObjectClass.h"

#include "GameObjectClass_Internal.h"
	#include "CraftClass_Internal.h"
		#include "ColonyClass_Internal.h"
		#include "RepairShipClass_Internal.h"
		#include "ProducerClass_Internal.h"

#include "MemRaider.h"


namespace mmm
{
	namespace
	{
		const std::size_t Function_GetODF = 0x004ce370;
	}

	GameObjectClassPtr 
	GameObjectClass::create( types::GameObjectClass* ptr )
	{
		return GameObjectClassPtr( new GameObjectClass( ptr ) );
	}

	GameObjectClass::GameObjectClass( types::GameObjectClass* goClass )
		: class_( goClass )
	{

	}

	GameObjectClass::~GameObjectClass( )
	{

	}

	const std::string
	GameObjectClass::getLabel() const
	{
		return class_->label;
	}

	const std::string
	GameObjectClass::getUnitString() const
	{
		return class_->unitString;
	}

	long
	GameObjectClass::getMaxSpecialEnergy() const
	{
		return class_->maxSpecialEnergy;
	}

	const std::string 
	GameObjectClass::getODF() const
	{
		return (class_->*memory_function<char* (types::GameObjectClass::*)()>(Function_GetODF))();
	}

	void
	GameObjectClass::setUnitString( const std::string& name )
	{
		//Fixed length C-strings are a pain. Why cant people just use string.
		//Actually, its kind of nice that they didn't since it makes changing
		//stuff easier.
		std::size_t length = name.size() > 0x3F ? 0x3F : name.size();
		memcpy( class_->unitString, name.c_str(), length );
		class_->unitString[length] = 0;
	}

	void
	GameObjectClass::setMaxSpecialEnergy( long value )
	{
		class_->maxSpecialEnergy = value;
	}

	types::GameObjectClass* 
	GameObjectClass::getClass() const
	{
		return class_;
	}

	

	GameObjectClassPtr 
	createGameObjectClassPtr( types::GameObjectClass* ptr )
	{
		//In order to spawn the correct type of entity, we must actually find out what the thing is.
		//We then call the function dependent on this.
		if( isGameObjectClass( ptr ) )
		{
			if( isTerrainObjectClass( ptr ) )
			{
				if( isAreaEffectObjectClass( ptr ) )
				{
					if( isWormholeClass( ptr ) )
					{
						//return WormholeClass::create( ptr );
					}
					else if( isNebulaClass( ptr ) )
					{
						//return NebulaClass::create( ptr );
					}
					else if( isIonStormClass( ptr ) )
					{
						//return IonStormClass::create( ptr );
					}
					else if( isBlackholeClass( ptr ) )
					{
						//return BlackHoleClass::create( ptr );
					}
					//return AreaEffectObjectClass::create( ptr );
				}
				if( isScrapClass( ptr ) )
				{
					//return ScrapClass::create( ptr );
				}
				else if( isUtritiumBallClass( ptr ) )
				{
					//return UtritiumBallClass::create( ptr );
				}
				else if( isBackgroundObjectClass( ptr ) )
				{
					if( isBackgroundPlanetClass( ptr ) )
					{
						//return BackgroundPlanetClass::create( ptr );
					}
					//return BackgroundObjectClass::create( ptr );
				}
				else if( isLatinumNebulaClass( ptr ) )
				{
					//return LatinumNebulaClass::create( ptr );
				}
				else if( isAsteroidFieldClass( ptr ) )
				{
					//return AsteroidFieldClass::create( ptr );
				}
				//return TerrainObjectClass::create( ptr );
			}
			else if( isCraftClass( ptr ) )
			{
				if( isProducerClass( ptr ) )
				{
					if( isPlanetClass( ptr ) )
					{
						//return PlanetClass::create( ptr );
					}
					else if( isMiningStationClass( ptr ) )
					{
						if( isTradingStationClass( ptr ) )
						{
							//return TradingStationClass::create( ptr );
						}
						//return MiningStationClass::create( ptr );
					}
					else if( isShipyardClass( ptr ) )
					{
						if( isStarbaseClass( ptr ) )
						{
							//return StarbaseClass::create( ptr );
						}
						//return ShipyardClass::create( ptr );
					}
					else if( isEvolverClass( ptr ) )
					{
						//return EvolverClass::create( ptr );
					}
					else if( isConstructionRigClass( ptr ) )
					{
						//return ConstructionRigClass::create( ptr );
					}
					else if( isResearchStationClass( ptr ) )
					{
						//return ResearchStationClass::create( ptr );
					}
					return ProducerClass::create( ptr );
				}
				else if( isFreighterClass( ptr ) )
				{
					//return FreighterClass::create( ptr );
				}
				else if( isRepairShipClass( ptr ) )
				{
					return RepairShipClass::create( ptr );
				}
				else if( isColonyClass( ptr ) )
				{
					return ColonyClass::create( ptr );
				}
				else if( isResearchPodClass( ptr ) )
				{
					//return ResearchPodClass::create( ptr );
				}
				else if( isCargoShipClass( ptr ) )
				{
					//return CargoShipClass::create( ptr );
				}
				else if( isScavengerClass( ptr ) )
				{
					//return ScavengerClass::create( ptr );
				}
				else if( isPlanetMiningBaseClass( ptr ) )
				{
					//return PlanetMiningBaseClass::create( ptr );
				}
				else if( isSensorArrayClass( ptr ) )
				{
					//return SensorArrayClass::create( ptr );
				}
				else if( isMineArrayClass( ptr ) )
				{
					//return MineArrayClass::create( ptr );
				}
				return CraftClass::create( ptr );
			}
			else if( isConstructionObjectClass( ptr ) )
			{
				//return ConstructionObjectClass::create( ptr );
			}

			return GameObjectClass::create( ptr );
		}

		return GameObjectClassPtr();
	}
}