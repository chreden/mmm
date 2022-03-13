#pragma once

#include "TerrainObject_Internal.h"

namespace mmm
{
	namespace types
	{
		struct BackgroundObject;
	}

	class BackgroundObject
		: public TerrainObject
	{
	public:
		static BackgroundObjectPtr create( types::Entity* entity );
		virtual GameObjectClassPtr getClass() const;
	protected:
		explicit	 BackgroundObject( types::BackgroundObject* object );
		virtual void allocateReplacement( luabind::detail::object_rep* object );
	};

	void backgroundobject_register( lua_State* state );
}
