#pragma once

#include "TerrainObject_Internal.h"

namespace mmm
{
	namespace types { struct Scrap; }

	class Scrap 
		: public TerrainObject
	{
	public:
		static ScrapPtr create( types::Entity* entity );
		virtual GameObjectClassPtr getClass() const;
	protected:
		explicit	   Scrap( types::Scrap* scrap );
		virtual void   allocateReplacement( luabind::detail::object_rep* object );
	};

	void scrap_register( lua_State* state );
}
