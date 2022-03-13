#pragma once

#include "BackgroundObject_Internal.h"

namespace mmm
{
	namespace types
	{
		struct BackgroundPlanet;
	}

	class BackgroundPlanet
		: public BackgroundObject
	{
	public:
		static BackgroundPlanetPtr create( types::Entity* entity );
		virtual GameObjectClassPtr getClass() const;
	protected:
		explicit	 BackgroundPlanet( types::BackgroundPlanet* planet );
		virtual void allocateReplacement( luabind::detail::object_rep* object );
	};

	void backgroundplanet_register( lua_State* state );
}
