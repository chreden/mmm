#pragma once

#include "Craft_Internal.h"

namespace mmm
{
	namespace types
	{
		struct RepairShip;
	}

	class RepairShip
		: public Craft
	{
	public:
		static RepairShipPtr create( types::Entity* entity );
		EntityPtr getRepairTarget( ) const;
		void	 setRepairTarget( EntityPtr ent );
	protected:
		explicit	 RepairShip( types::RepairShip* ship );
		virtual void allocateReplacement( luabind::detail::object_rep* obj );
	private:
		types::RepairShip* getRepairShip() const;
	};

	void repairship_register( lua_State* state );
}
