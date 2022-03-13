#pragma once

#include "Producer.h"

namespace mmm
{
	namespace types
	{
		class Shipyard;
	}

	class Shipyard
		: public Producer
	{
	public:
		static ShipyardPtr create( types::Entity* entity );
			
		EntityPtr		 getWormhole( ) const;
		EntityPtr		 getRepairingShip( ) const;
		const Vector3	 getRallyPoint( ) const;
		OrientedQueuePtr getRepairQueue() const;

		void setRallyPoint( const Vector3& point );
		void setWormhole( EntityPtr wormhole );
		types::Shipyard* getShipyard() const;
	protected:
		explicit	   Shipyard( types::Shipyard* shipyard );
		virtual void   allocateReplacement( luabind::detail::object_rep* object );
	};

	void shipyard_register( lua_State* state );
}
