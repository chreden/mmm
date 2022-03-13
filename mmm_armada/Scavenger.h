#pragma once

#include "Craft_Internal.h"

namespace mmm
{
	namespace types { struct Scavenger; }

	class Scavenger
		: public Craft
	{
	public:
		static ScavengerPtr create( types::Entity* scavenger );
	protected:
		virtual void allocateReplacement( luabind::detail::object_rep* object );
	private:
		explicit Scavenger( types::Scavenger* scavenger );
	};

	void scavenger_register( lua_State* state );
}
