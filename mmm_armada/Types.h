#pragma once

#include "ST3D_Colour.h"
#include "Vector3.h"

namespace mmm
{
	namespace types
	{
		struct Entity;
		struct AiPath;
	}

	struct CargoDesc
	{
		char	key[0x40];
		float	value;
	};

	struct Matrix34
	{
		Vector3 right;
		Vector3 up;
		Vector3 forward;
		Vector3 position;
	};

	struct Euler
	{
		Vector3 omega, accel, alpha, m_vel;
	};

	enum EntityType
	{
		Type_Ordnance			= 0x1,
		Type_Explosion			= 0x2,
		Type_GameObject			= 0x4,
		Type_Craft				= 0x8,
		//Type_WHAT				= 0x10,
		Type_Producer			= 0x20,
		Type_Rig				= 0x40,
		Type_Freighter			= 0x80,
		Type_SensorArray		= 0x100,
		Type_Shipyard			= 0x200,
		Type_Starbase			= 0x400,
		Type_ResearchStation	= 0x800,
		Type_ResearchPod		= 0x1000,
		Type_Nebula				= 0x2000,
		Type_Wormhole			= 0x4000,
		Type_AsteroidField		= 0x8000, 
		Type_BackgroundObject	= 0x10000,
		Type_Blackhole			= 0x20000,
		Type_ConstructionObject = 0x40000,
		Type_IonStorm			= 0x80000,
		Type_Scrap				= 0x100000,
		Type_MiningStation		= 0x200000,
		Type_Scavenger			= 0x400000,
		Type_Beam				= 0x800000,
		Type_BeamToggle			= 0x1000000,
		Type_Bullet				= 0x2000000,
		Type_Missile			= 0x4000000,
		Type_Mine				= 0x8000000,
		Type_ShockwaveExplosion = 0x10000000,
		Type_PointDefenseLaser  = 0x20000000,
		Type_HoldingBeam		= 0x40000000,
		Type_CargoShip			= 0x80000000 
	};

	enum eCivPopulationLevel
	{
		UNPOPULATED_LEVEL = 0,
		SPARSE_LEVEL,
		LIGHT_LEVEL,
		MEDIUM_LEVEL,
		HEAVY_LEVEL,
		NUM_POP_LEVELS
	};

	enum eTeamRelation
	{
		TEAM_ENEMY = 0,
		TEAM_NEUTRAL = 1,
		TEAM_ALLY = 2
	};

	enum eMineStatus
	{
		StateDeploy,
		StateDetect,
		StateChase
	};

	enum eDockingState
	{
		JustDocked,
		LoadCargo,
		UnloadCargo,
		Exit
	};

	enum eResource
	{
		RESOURCE_CREW = 0,
		RESOURCE_OFFICERS,
		RESOURCE_DILITHIUM,
		RESOURCE_LATINUM,
		RESOURCE_METAL,
		RESOURCE_BIOMATTER,
		NUMBER_OF_RESOURCES
	};

	enum eMineArrayState 
	{
		MINE_ARRAY_DO_NOTHING = 0x0,
		MINE_ARRAY_FIND_TARGET = 0x1,
		MINE_ARRAY_FIND_HOME = 0x2,
	};

	//I made this one
	enum eSlotType
	{
		ST_None = 0,
		ST_Human,
		ST_Observer,
		ST_AI_Easy,
		ST_AI_Normal,
		ST_AI_Hard,
		ST_AI_Neural
	};

	enum eAlertStatus
	{
		ALERT_STATUS_RED = 0,
		ALERT_STATUS_YELLOW,
		ALERT_STATUS_GREEN
	};

	enum eMovementAutonomy
	{
		MOVEMENT_AUTONOMY_LOW = 0,
		MOVEMENT_AUTONOMY_MED,
		MOVEMENT_AUTONOMY_HIGH
	};

	enum eSpecialWeaponAutonomy
	{
		SPECIAL_WEAPON_AUTONOMY_NONE = 0,
		SPECIAL_WEAPON_AUTONOMY_MED,
		SPECIAL_WEAPON_AUTONOMY_HIGH
	};

	enum eCraftSystem
	{
		Engines = 0,
		LifeSupport, 
		Shields,
		Weapons,
		Sensors
	};

	enum GateStatus
	{
		Gate_Closed = 0,
		Gate_Close,
		Gate_Open,
		Gate_Opening
	};

	//Used to tell ships to do something.
	enum AiCommand
	{
		CMD_NONE = 0,
		CMD_DEFAULT,
		CMD_SELECT,
		CMD_STOP,
		CMD_GO,						
		CMD_GO_SINGLE,				
		CMD_ATTACK,					//Done
		CMD_SPECIAL_ATTACK,			
		CMD_ANCHORED_ATTACK,
		CMD_TRANSPORT_ATTACK,
		CMD_QUEUE,
		CMD_FOLLOW,
		CMD_FORMATION,
		CMD_TRANSPORT,	
		CMD_TRANSPORT_SPECIAL,
		CMD_RECREW,					//Done
		CMD_SET_RALLY_POINT,
		CMD_GET_REPAIR,				//Done
		CMD_DEFEND,
		CMD_CANCEL_BUILD,
		CMD_DECOMMISSION,			//Done
		CMD_MINE,
		CMD_SEARCH_AND_DESTROY,		//Done
		CMD_GUARD,	
		CMD_SCOUT,					//Done
		CMD_BUILD,					//Done
		CMD_PATROL,					//Doneish
		CMD_RED_ALERT,
		CMD_YELLOW_ALERT,
		CMD_GREEN_ALERT,
		CMD_CANCEL_BUILD_QUEUE_ITEM,
		CMD_WORMHOLE,
		CMD_FORMFORMATION,
		CMD_GORALLY,
		CMD_START_TRADE,
		CMD_END_TRADE,
		CMD_TRADING,
		CMD_GIVERESOURCE,
		CMD_COLONIZE,
		CMD_REPAIR_OTHER,
		CMD_BUY_RESOURCE,
		CMD_SELL_RESOURCE,
		CMD_SET_FORMATION,
		CMD_GO_WARP,
		CMD_GO_WARP_SINGLE,
		CMD_SET_ATTACK_MODE,
		CMD_SPECIAL_WEAPON_AUTONOMY_NONE,
		CMD_SPECIAL_WEAPON_AUTONOMY_MED,
		CMD_SPECIAL_WEAPON_AUTONOMY_HIGH,
		CMD_MOVE_LOW,
		CMD_MOVE_MED,
		CMD_MOVE_HIGH,
		CMD_WEAPON_QUEUE,
		CMD_GET_SUPER_REPAIR,
		CMD_SET_FORMATION_ORIENTATION,
		CMD_RECYCLE_METAL,
		CMD_RECYCLE_DILITHIUM,
		NUM_CMD
	};



	enum eJustify
	{
		JUSTIFY_TOP_LEFT = 0,
		JUSTIFY_TOP_RIGHT = 1,
		JUSTIFY_TOP_CENTER = 2,
		JUSTIFY_BOTTOM_LEFT = 4,
		JUSTIFY_BOTTOM_RIGHT = 5,
		JUSTIFY_BOTTOM_CENTER = 6,
		JUSTIFY_CENTER_LEFT = 8,
		JUSTIFY_CENTER_RIGHT = 9,
		JUSTIFY_CENTER = 10,
		JUSTIFY_TOP_LEFT_BY_LINE = 16,
		JUSTIFY_TOP_RIGHT_BY_LINE = 17,
		JUSTIFY_TOP_CENTER_BY_LINE = 18,
		JUSTIFY_BOTTOM_LEFT_BY_LINE = 20,
		JUSTIFY_BOTTOM_RIGHT_BY_LINE = 21,
		JUSTIFY_BOTTOM_CENTER_BY_LINE = 22,
		JUSTIFY_CENTER_LEFT_BY_LINE = 24,
		JUSTIFY_CENTER_RIGHT_BY_LINE = 25,
		JUSTIFY_CENTER_BY_LINE = 26
	};
		
	struct GameFeature
	{
		virtual void Init( ) = 0;
		virtual void Cleanup( ) = 0;
		virtual void PreLoad( ) = 0;
		virtual void PostLoad( ) = 0;
		virtual void PreDestroy( ) = 0;

		virtual void PostRun( ) = 0;

		virtual void Control( ) = 0;
		virtual void Simulate ( ) = 0;
		virtual void Render( void* , unsigned char ) = 0;
		virtual void AddEntity( void* ) = 0;
		virtual void DeleteEntity( void* ) = 0;
		virtual void AddObject( void* ) = 0;
		virtual void DeleteObject( void* object ) = 0;

		static std::vector<GameFeature*> features;
		int initPriority;
		int cleanupPriority;
		int preLoadPriority;
		int postLoadPriority;
		int preDestroyPriority;
		int postRunPriority;
		int renderPriority;
		unsigned char needsControl;
		unsigned char needsSimulate;
		unsigned char needsRender;
	};

	enum Argument_Type
	{
		ARG_NONE = 0,
		ARG_PATH,
		ARG_OBJECT,
		ARG_OBJECT_CLASS
	};

	struct PartialCommandInfo
	{
		Argument_Type argument_type; 
		int what;
		int who;
		Vector3 location; 
		int param;
		unsigned char turnon;
	};

	struct AiCmdInfo
	{
		Argument_Type argumentType; //ARG_NONE, Argument_TYPE
		int what; //AI COMMAND
		int who; 
		types::AiPath* where; //AI Path
		long param; 
		Vector3 actualWhere; //Actual
		void* pObjectClass; //
		void* pWeaponClass; //
		unsigned char voiceOvers;
		unsigned char fullyPlannedPath;
		unsigned char turnOn;
		std::vector<int>* pTeamMates;
	};

	struct EffectInfo
	{
		char name[26];
		int build;
	};

	struct SpecialObjectEffect
	{
		static int typeCount;
		static int typeID;
		static std::list<SpecialObjectEffect*> mAllEffects;
		static std::vector<EffectInfo*> mEffectType;
		int mWeaponFired;
		int mVictim;
		int mRemoveMe;
		int mSystemType;
		int mDamage;
		int mOwnerHandle;
		int mOwnerTeam;
		char* mName;
		int m_removableByShipyard;
		int m_removableByRepairShip;
	};

	typedef std::list<SpecialObjectEffect*> EffectList;
		
		

	union EntityID
	{
		int m_id;
		struct
		{
			int m_index : 15;
			int m_sequence : 16;
			int m_used : 1;
		};
	};

	namespace types
	{
		struct Entity;
		class Transport { };
	}

	struct EntityPointer
	{
		EntityID m_id;
		union
		{
			types::Entity* m_entity;
			EntityPointer* m_nextFree;
		};
	};

	struct EntityPointerManager : public GameFeature
	{
		static constexpr int MaxEntities = 16384;

		virtual void PostRun( ) = 0;

		EntityPointer m_entity_pointer[MaxEntities];
		int m_active_entities;
		int m_active_entities_highest;
		EntityPointer* m_first_free;
		unsigned char m_entity_manager_online;
	};

	inline
	const EntityID createEntityID( int index )
	{
		EntityID ent;
		ent.m_id = index;
		return ent;
	}

	inline
	EntityPointerManager* GetEntityPointerManager( )
	{
		return reinterpret_cast<EntityPointerManager*>( 0x00741000 );
	}

	inline
	EntityPointer* GetEntityPointer( )
	{
		return GetEntityPointerManager( )->m_entity_pointer;
	}

	template<typename T>
	T* LoadMemPointer( std::size_t address )
	{
		return *reinterpret_cast<T**>( address );
	}

	template<typename T>
	T& GetMemVariable( const std::size_t address )
	{
		return *reinterpret_cast<T*>( address );
	}

	template<typename T>
	void SetMemVariable( const T& value, const std::size_t address )
	{
		*reinterpret_cast<T*>( address ) = value;
	}

	inline
	void* FindGameObjectClass( const char* odf )
	{
		typedef void* (*Finder)( const char* );
		Finder find = memory_function< Finder >( 0x004cd370 );
			
		return find( odf );
	}

	struct MessageMark
	{
		Vector3 m_location;
		float	m_shrinkRate;
		float	m_timer;
		float	m_totalTime;
		int		m_maxRadius;
		int		m_radius;
		ST3D_Colour m_color;
		static int s_defaultRadius;
		static float s_defaultShrinkRate;
	};

	class MapRadar { };

	class hot_int 
	{
	public:
		char _padding_[0x20];
		int  value;
	};

	class hot_float
	{
	};

	class character { };

	class IIIE { };

	class rule { };

	class MetaFont { };

	class OverlayText { };

	struct ScreenFade
	{
		char _padding_[0x15];
		unsigned char isHidden;
		char _padding_2[0xE];

		enum FadeState
		{
			STATE_NOFADE = 0,
			STATE_FADE_OUT,
			STATE_FADE_IN
		};

		enum FadeType
		{
			FADE_TYPE_BLACK = 0,
			FADE_TYPE_WHITE
		};

		FadeState	m_fadeState;
		FadeType	m_fadeType;
		float		m_current_transparency;
		float		m_current_transparency_delta;
		float		m_overtime;
		float		m_delaytime;
		void*		m_calledFromScript;
	};

	struct CommandLine { };
	//0x007aeb0c

	namespace types
	{
		struct GameObjectClass;
		struct BuildQueueItem
		{
			GameObjectClass* m_next_obj;
			BuildQueueItem*  m_prev;
			BuildQueueItem*	 m_next;
			int				 m_build_queue_item_id;
		};

		
	}

	enum Special
		{
			Standard = 0,
			StandardIgnoreShield = 1,
			IgnoreShield = 2,
			DisableEngines = 4,
			DisableLifesupport = 8,
			DisableWeapons = 16,
			DisableShields = 32,
			DisableSensors = 64,
			DamageShieldsOnly = 128
		};
}
