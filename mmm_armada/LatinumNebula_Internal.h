#pragma once

#include "TerrainObject_Internal.h"

namespace mmm
{
	namespace types
	{
		struct LatinumNebula;
	}

	class LatinumNebula
		: public TerrainObject
	{
	public:
		static LatinumNebulaPtr create( types::Entity* entity );
		virtual GameObjectClassPtr getClass() const;
	protected:
		explicit	 LatinumNebula( types::LatinumNebula* nebula );
		virtual void allocateReplacement( luabind::detail::object_rep* object );
	};

	void latinumnebula_register( lua_State* state );
}
