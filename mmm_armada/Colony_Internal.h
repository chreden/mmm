#pragma once

#include "Craft_Internal.h"

namespace mmm
{
	namespace types
	{
		struct Colony;
	}

	class Colony
		: public Craft
	{
	public:
		static ColonyPtr create( types::Entity* entity );

		EntityPtr	getPlanet() const;
		int			getColonists() const;
		int			getInitialColonists() const;
		float		getInitialPopulation() const;

		void	setColonists( int value );
		void	setInitialColonists( int value );
		void	setInitialPopulation( float value );
	protected:
		explicit	 Colony( types::Colony* colony );
		virtual void allocateReplacement( luabind::detail::object_rep* object );
	private:
		types::Colony* getColony() const;
	};

	void colony_register( lua_State* state );
}
