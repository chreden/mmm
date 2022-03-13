#pragma once

#include "ProducerClass_Internal.h"

namespace mmm
{
	namespace types
	{
		struct EvolverClass;
	}

	class EvolverClass
		: public ProducerClass
	{
	public:
		explicit EvolverClass( types::EvolverClass* evolver );
	};

	void evolverclass_register( lua_State* state );
}
