#pragma once

#include "Craft_Internal.h"

namespace mmm
{
	namespace types { struct PlanetMiningBase; }

	class PlanetMiningBase
		: public Craft
	{
	public:
		static PlanetMiningBasePtr create( types::Entity* entity );

		EntityPtr getPlanet() const;
		float	  getOrbitOmega() const;
		int		  getNumHoldingBeams() const;

		void	  setPlanet( EntityPtr ent );
		void	  setOrbitOmega( float value );
		void	  setNumHoldingBeams( int value );
	protected:
		virtual void allocateReplacement( luabind::detail::object_rep* object );
	private:
		explicit PlanetMiningBase( types::PlanetMiningBase* base );
		types::PlanetMiningBase* getPlanetMiningBase() const;
	};

	void planetminingbase_register( lua_State* state );
}
