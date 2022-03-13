#pragma once

#include "ProducerClass_Internal.h"

namespace mmm
{
	namespace types { struct MiningStationClass; }

	class MiningStationClass
		: public ProducerClass
	{
	public:
		explicit MiningStationClass( types::MiningStationClass* station );
	private:
		types::MiningStationClass* getMiningStationClass() const;
	};

	void miningstationclass_register( lua_State* state );
}
