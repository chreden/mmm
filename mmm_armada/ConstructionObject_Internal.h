#pragma once

#include "GameObject_Internal.h"

namespace mmm
{
	namespace types
	{
		struct ConstructionObject;
	}

	class ConstructionObject
		: public GameObject
	{
	public:
		static ConstructionObjectPtr create( types::Entity* entity );
		types::ConstructionObject* getConstructionObject() const;

		EntityPtr			getBuilder() const;
		GameObjectClassPtr  getBuildClass() const;
	protected:
		explicit	   ConstructionObject( types::ConstructionObject* object );
		virtual void   allocateReplacement( luabind::detail::object_rep* object );			
	};

	void constructionobject_register( lua_State* state );
}
