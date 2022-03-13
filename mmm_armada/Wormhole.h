#pragma once

#include "AreaEffectObject_Internal.h"

namespace mmm
{
	namespace types
	{
		struct Wormhole;
	}

	class Wormhole
		: public AreaEffectObject
	{
	public:
		static WormholePtr create( types::Entity* entity );

		WormholePtr			getPartner( ) const;
		GateStatus			getStatus( ) const;
		const std::string	getName( ) const;
		TeamPtr				getOwner( ) const;

		bool getExpireOnClose() const;
		bool getDeleteOnTransport() const;

		bool setPartner( EntityPtr other );
		void setExpireOnClose( bool value );
		void setDeleteOnTransport( bool value );
		void setName( const std::string& name );
		void setStatus( GateStatus status );
		void setOwner( TeamPtr owner );
		void setShipyard( ShipyardPtr shipyard );
		types::Wormhole* getWormhole() const;
	protected:
		explicit Wormhole( types::Wormhole* wormhole );
		virtual void   allocateReplacement( luabind::detail::object_rep* object );
	};

	void wormhole_register( lua_State* state );
}
