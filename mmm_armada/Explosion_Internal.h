#pragma once

#include "Entity_Internal.h"

namespace mmm
{
	namespace types
	{
		struct Explosion;
	}

	class Explosion
		: public Entity
	{
	public:
		explicit Explosion( types::Explosion* explosion );

		EntityPtr	getEntityResponsible() const;
		float		getRadius( ) const;
		bool		getSoundPlayed() const;

		types::Explosion* getExplosion( ) const;
	};

	void explosion_register( lua_State* state );
}
