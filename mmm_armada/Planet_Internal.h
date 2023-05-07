#pragma once

#include "Producer.h"

namespace mmm
{
	namespace types 
	{ 
		struct Planet; 
	} 

	class Planet :
		public Producer
	{
	public:
		static PlanetPtr create( types::Entity* entity );
		EntityPtr getColonyShip() const;
		eCivPopulationLevel getPopulationLevel() const;
		float	 getPopulation() const;
		float	 getMaxPopulation() const;
		std::shared_ptr<Race> getOldRace() const;
		bool	 getHasShields() const;
		void	 setPopulation( float value );
	protected:
		explicit	   Planet( types::Planet* planet );
		virtual void   allocateReplacement( luabind::detail::object_rep* object );
	private:
		types::Planet* getPlanet() const;
	};

	void planet_register( lua_State* state );
}
