#pragma once

#include "Craft_Internal.h"

namespace mmm
{
	namespace types { struct CargoShip; }

	class CargoShip
		: public Craft
	{
	public:
		static CargoShipPtr create( types::Entity* entity );
		//Properties that are part of the actual cargo ship
		EntityPtr	getStartStation() const;
		EntityPtr	getDestinationStation() const;
		bool		getIsTrading() const;
		float		getMaxCargo() const;
		eResource	getNextResource() const;
		//Actual goods properties
		float		getCargoAmount() const;
		eResource	getResource() const;
		std::string getCargoName() const;
		bool		getIsFull() const;

	protected:
		explicit	 CargoShip( types::CargoShip* cargoShip );
		virtual void allocateReplacement( luabind::detail::object_rep* object );
	private:
		types::CargoShip* getCargoShip() const;
	};

	void cargoship_register( lua_State* state );
}
