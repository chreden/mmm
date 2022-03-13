#pragma once

#include "TerrainObject_Internal.h"

namespace mmm
{
	namespace types
	{
		struct AreaEffectObject;
	}

	class AreaEffectObject 
		: public TerrainObject
	{
	public:
		static AreaEffectObjectPtr create( types::Entity* entity );
		virtual GameObjectClassPtr getClass() const;
	protected:
		explicit	   AreaEffectObject( types::AreaEffectObject* object );
		virtual void   allocateReplacement( luabind::detail::object_rep* object );
	};

	void areaeffectobject_register( lua_State* state );
}
