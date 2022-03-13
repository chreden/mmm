#include "Craft_Internal.h"
#include "CraftSystem_Internal.h"
#include "CraftClass_Internal.h"
#include "Type_Craft.h"
#include "Type_Entity.h"
#include "Type_CraftSystem.h"
#include "Type_CraftClass.h"

namespace mmm
{
	namespace
	{
		const std::size_t Address_Explode = 0x004c6ab0;
		const std::size_t Address_GetAlertStatus = 0x004c9a20;
		const std::size_t Address_SetAlertStatus = 0x004c9a50;
		const std::size_t Address_GetSpecialWeaponAutonomy = 0x004c9ae0;
		const std::size_t Address_SetSpecialWeaponAutonomy = 0x004c9b10;
		const std::size_t Address_GetMovementAutonomy = 0x004c9b40;
		const std::size_t Address_SetMovementAutonomy = 0x004c9b70;
		const std::size_t Address_DisableEngines = 0x004c9ef0;
		const std::size_t Address_DisableLifeSupport = 0x004c9f80;
		const std::size_t Address_DisableShieldGenerator = 0x004ca010;
		const std::size_t Address_DisableWeapons = 0x004ca090;
		const std::size_t Address_DisableSensors = 0x004ca110;
		const std::size_t Address_PermanentDisableEngines = 0x004ca1a0;
		const std::size_t Address_PermanentDisableLifeSupport = 0x004ca230;
		const std::size_t Address_PermanentDisableShieldGenerator = 0x004ca2c0;
		const std::size_t Address_PermanentDisableWeapons = 0x004ca350;
		const std::size_t Address_PermanentDisableSensors = 0x004ca3e0;
		const std::size_t Address_GetShields = 0x004c8a50;
		const std::size_t Address_SetName = 0x004c1f00;
		const std::size_t Address_SetCrew = 0x004c83e0;
		const std::size_t Address_SetMaximumCrew = 0x004c8430;
	}

	CraftPtr
	Craft::create( types::Entity* entity )
	{
		return CraftPtr( new Craft( static_cast<types::Craft*>( entity ) ) );
	}

	Craft::Craft( types::Craft* craft )
		: GameObject( craft )
	{

	}

	types::Craft* 
	Craft::getCraft() const
	{
		return static_cast<types::Craft*>( getEntity( ) );
	}

	const std::string 
	Craft::getName( ) const
	{
		types::Craft* craft = getCraft();
		if( craft && craft->m_pCraftName )
		{
			return craft->m_pCraftName;
		}
		return "";
	}
		
	float 
	Craft::getShields( ) const
	{
		return (getCraft()->*memory_function< float (types::Craft::*) ( ) >( Address_GetShields ))();
	}

	float
	Craft::getShieldsValue( ) const
	{
		return getCraft()->m_curShields;
	}

	float
	Craft::getMaxShields( ) const
	{
		return getCraft()->m_maxShields;
	}

	eAlertStatus 
	Craft::getAlertStatus( ) const
	{
		return (getCraft()->*memory_function< eAlertStatus (types::Craft::*) () >( Address_GetAlertStatus ))();
	}

	eSpecialWeaponAutonomy
	Craft::getSpecialWeaponAutonomy( ) const
	{
		return (getCraft()->*memory_function< eSpecialWeaponAutonomy (types::Craft::*)() >( Address_GetSpecialWeaponAutonomy ))();
	}

	eMovementAutonomy 
	Craft::getMovementAutonomy( ) const
	{
		return (getCraft()->*memory_function< eMovementAutonomy (types::Craft::*)() >( Address_GetMovementAutonomy ))();
	}

	float
	Craft::getImpulseSpeed( ) const
	{
		return getScriptInterface()->GetImpulseSpeed( getCraft()->m_entity_id );
	}

	float 
	Craft::getCrew( ) const
	{
		return getCraft()->m_curCrew;
	}
		
	float 
	Craft::getMaxCrew( ) const
	{
		return getCraft()->m_maxCrew;
	}

	luabind::object
	Craft::getSystems()
	{
		//Create a new table to store the systems - the user can access them from there.
		//Each system contains a pointer to the actual system so they can update the 
		//actual values of the system.
		luabind::object systems = luabind::newtable(common::Storage::instance().mainLuaVM);

		//Store each of the craft systems that we have in the array. Craft systems cannot
		//be created by the user so there is no worry of overwrite or anything.

		CraftPtr self = boost::static_pointer_cast<Craft>(shared_from_this());
		systems["shields"] = CraftSystemPtr( new CraftSystem( self, &getCraft()->m_pCraftSystem[0] ) );
		systems["engines"] = CraftSystemPtr( new CraftSystem( self, &getCraft()->m_pCraftSystem[1] ) );
		systems["weapons"] = CraftSystemPtr( new CraftSystem( self, &getCraft()->m_pCraftSystem[2] ) );
		systems["lifeSupport"] = CraftSystemPtr( new CraftSystem( self, &getCraft()->m_pCraftSystem[3] ) );
		systems["sensors"] = CraftSystemPtr( new CraftSystem( self, &getCraft()->m_pCraftSystem[4] ) );
			
		return systems;
	}

	GameObjectClassPtr 
	Craft::getClass() const
	{
		return createGameObjectClassPtr( getGameObject()->m_class );
	}

	void 
	Craft::setName( const std::string& name )
	{
		(getCraft()->*memory_function< void (types::Craft::*)(const char*) >( Address_SetName ))( name.c_str() );
	}

	void 
	Craft::setShields( float percentage )
	{
		getCraft()->m_curShields = getMaxShields() * percentage;
	}

	void
	Craft::setShieldsValue( float value )
	{
		getCraft()->m_curShields = value;
	}

	void
	Craft::setMaxShields( float value )
	{
		getCraft()->m_maxShields = value;
	}

	void 
	Craft::setCrew( float value )
	{
		(getCraft()->*memory_function< void (types::Craft::*)( float ) >( Address_SetCrew ))( value );
	}

	void 
	Craft::setMaxCrew( float value )
	{
		(getCraft()->*memory_function< void (types::Craft::*)( float ) >( Address_SetMaximumCrew ))( value );
	}

	void 
	Craft::setAlertStatus( eAlertStatus status )
	{
		(getCraft()->*memory_function< void (types::Craft::*)(eAlertStatus) >( Address_SetAlertStatus ))(status);
	}

	void
	Craft::setSpecialWeaponAutonomy( eSpecialWeaponAutonomy autonomy )
	{
		(getCraft()->*memory_function< void (types::Craft::*)(eSpecialWeaponAutonomy) >( Address_SetSpecialWeaponAutonomy ))( autonomy );
	}

	void
	Craft::setMovementAutonomy( eMovementAutonomy autonomy )
	{
		(getCraft()->*memory_function< void (types::Craft::*)(eMovementAutonomy) >( Address_SetMovementAutonomy ))( autonomy );
	}

	void 
	Craft::setSystemStatus( eCraftSystem system, bool state )
	{
		typedef void (types::Craft::*MemFunction)( bool );
		MemFunction function = 0;

		switch( system )
		{
		case Engines:
			function = memory_function< MemFunction >( Address_PermanentDisableEngines );
			break;
		case LifeSupport:
			function = memory_function< MemFunction >( Address_PermanentDisableLifeSupport );
			break;
		case Shields:
			function = memory_function< MemFunction >( Address_PermanentDisableShieldGenerator );
			break;
		case Weapons:
			function = memory_function< MemFunction >( Address_PermanentDisableWeapons );
			break;
		case Sensors:
			function = memory_function< MemFunction >( Address_PermanentDisableSensors );
			break;
		}

		if( function )
		{
			(getCraft()->*function)( !state );
		}
	}

	void
	Craft::setImpulseSpeed( float value )
	{
		getScriptInterface()->SetImpulseSpeed( getCraft()->m_entity_id, value );
	}

	void 
	Craft::explode( )
	{
		(getCraft()->*memory_function< void (types::Craft::*)() >( Address_Explode ))();
	}

	void 
	Craft::disableSystem( eCraftSystem system, float time )
	{
		typedef void (types::Craft::*MemFunction) ( float );
		MemFunction function = 0;

		switch( system )
		{
		case Engines:
			function = memory_function< MemFunction >( Address_DisableEngines );
			break;
		case LifeSupport:
			function = memory_function< MemFunction >( Address_DisableLifeSupport );
			break;
		case Shields:
			function = memory_function< MemFunction >( Address_DisableShieldGenerator );
			break;
		case Weapons:
			function = memory_function< MemFunction >( Address_DisableWeapons );
			break;
		case Sensors:
			function = memory_function< MemFunction >( Address_DisableSensors );
			break;
		}

		if( function )
		{
			(getCraft()->*function)( time );
		}
	}

	void
	Craft::allocateReplacement( luabind::detail::object_rep* obj )
	{
		entity_allocate_replacement<Craft>( obj, boost::static_pointer_cast<Craft>( shared_from_this() ) );
	}
}