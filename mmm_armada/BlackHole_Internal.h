#pragma once

#include "AreaEffectObject_Internal.h"

namespace mmm
{
	namespace types { struct BlackHole; }

	class BlackHole
		: public AreaEffectObject
	{
	public:
		static BlackHolePtr		   create( types::Entity* entity );
		virtual GameObjectClassPtr getClass() const;
	protected:
		explicit	   BlackHole( types::BlackHole* type );
		virtual void   allocateReplacement( luabind::detail::object_rep* object );
	};

	void blackhole_register( lua_State* state );
}
