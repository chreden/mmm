#pragma once

#include "Shipyard_Internal.h"

namespace mmm
{
	namespace types
	{
		struct Starbase;
	}

	class Starbase
		: public Shipyard
	{
	public:
		static StarbasePtr create( types::Entity* entity );
	protected:
		explicit	   Starbase( types::Starbase* starbase );
		virtual void   allocateReplacement( luabind::detail::object_rep* object );
	private:
		types::Starbase* getStarbase() const;
	};

	void starbase_register( lua_State* state );
}
