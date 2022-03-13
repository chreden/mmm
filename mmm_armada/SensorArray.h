#pragma once

#include "Craft_Internal.h"

namespace mmm
{
	namespace types { struct SensorArray; }

	class SensorArray
		: public Craft
	{
	public:
		static SensorArrayPtr create( types::Entity* entity );
	protected:
		virtual void allocateReplacement( luabind::detail::object_rep* object );
	private:
		explicit SensorArray( types::SensorArray* sensor );
	};

	void sensorarray_register( lua_State* state );
}
