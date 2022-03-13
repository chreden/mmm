#pragma once

#include "CraftClass_Internal.h"

namespace mmm
{
	namespace types
	{
		struct RepairShipClass;
	}

	class RepairShipClass
		: public CraftClass
	{
	public:
		static RepairShipClassPtr create( types::GameObjectClass* ptr );
		float	getRepairRate() const;
		void	setRepairRate( float value );
	private:
		explicit RepairShipClass( types::RepairShipClass* ship );
		types::RepairShipClass* getRepairShipClass() const;
	};

	void repairshipclass_register( lua_State* state );
}
