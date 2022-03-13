#pragma once

#include "MiningStation.h"

namespace mmm
{
	namespace types { struct TradingStation; }

	class TradingStation
		: public MiningStation
	{
	public:
		static TradingStationPtr create( types::Entity* entity );
		virtual GameObjectClassPtr getClass() const;

		eDockingState getDockingState() const;
		Vector3		  getRallyPoint() const;
		EntityPtr	  getDockedFerengi() const;
		void		  setRallyPoint( const Vector3& rallyPoint );
	protected:
		explicit	 TradingStation( types::TradingStation* station );
		virtual void allocateReplacement( luabind::detail::object_rep* object );
	private:
		types::TradingStation* getTradingStation() const;
	};

	void tradingstation_register( lua_State* state );
}