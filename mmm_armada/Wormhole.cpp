#include "Wormhole.h"
#include "WormholeType.h"
#include "Team_Internal.h"
#include "Shipyard_Internal.h"

namespace mmm
{
	namespace
	{
		const std::size_t Offset_State			= 0x00000190;
		const std::size_t Offset_Name			= 0x000001BE;
		const std::size_t Address_SetPartner		= 0x004a6a60;
		const std::size_t Address_SetShipyard	= 0x004a77f0;
		const std::size_t Address_SetName		= 0x004a7860;
	}

	WormholePtr 
	Wormhole::create( types::Entity* entity )
	{
		return WormholePtr( new Wormhole( static_cast<types::Wormhole*>( entity ) ) );
	}

	Wormhole::Wormhole( types::Wormhole* wormhole )
		: AreaEffectObject( wormhole )
	{

	}

	WormholePtr 
	Wormhole::getPartner( ) const
	{
		return WormholePtr( new Wormhole( getWormhole()->m_pWormholePartner ) );
	}

	GateStatus
	Wormhole::getStatus( ) const
	{
		return getWormhole()->m_wormholeState;
	}

	const std::string 
	Wormhole::getName( ) const
	{
		return getWormhole()->m_pDisplayName;
	}

	TeamPtr
	Wormhole::getOwner( ) const
	{
		return TeamPtr( new Team( getWormhole()->m_ownerTeam ) );
	}

	bool 
	Wormhole::setPartner( EntityPtr wormhole )
	{
		if( wormhole->isType( Entity_Wormhole ) )
		{
			typedef void (types::Wormhole::*MemFunction) ( types::Wormhole* );
			MemFunction function = memory_function<MemFunction>( Address_SetPartner );
			(getWormhole()->*function)( static_cast<types::Wormhole*>( wormhole->getEntity() ) );
			return true;
		}
		return false;
	}

	bool 
	Wormhole::getExpireOnClose() const
	{
		return getWormhole()->m_expireOnClose;
	}
		
	bool 
	Wormhole::getDeleteOnTransport() const
	{
		return getWormhole()->m_deleteOnTransport;
	}

	void 
	Wormhole::setExpireOnClose( bool value )
	{
		getScriptInterface()->SetWormholeExpireOnClose( getWormhole()->m_entity_id, value );
	}

	void
	Wormhole::setDeleteOnTransport( bool value )
	{
		getScriptInterface()->SetWormholeDeleteOnTransport( getWormhole()->m_entity_id, value );
	}

	void 
	Wormhole::setName( const std::string& name )
	{
		typedef void (types::Wormhole::*MemFunction) ( const char* );
		MemFunction function = memory_function<MemFunction>( Address_SetName );
		(getWormhole()->*function)( name.c_str() );
	}

	void
	Wormhole::setOwner( TeamPtr team )
	{
		getWormhole()->m_ownerTeam = team->getNumber();
	}

	void 
	Wormhole::setShipyard( ShipyardPtr shipyard )
	{
		(getWormhole()->*memory_function<void (types::Wormhole::*)(types::Shipyard*) >( Address_SetShipyard ))( shipyard->getShipyard() );
	}

	types::Wormhole* 
	Wormhole::getWormhole() const
	{
		return static_cast<types::Wormhole*>( getEntity() );
	}

	void
	Wormhole::allocateReplacement( luabind::detail::object_rep* obj )
	{
		entity_allocate_replacement<Wormhole>( obj, boost::static_pointer_cast<Wormhole>( shared_from_this() ) );
	}
}
