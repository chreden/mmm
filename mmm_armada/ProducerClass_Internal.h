#pragma once

#include "CraftClass_Internal.h"

namespace mmm
{
	namespace types
	{
		struct ProducerClass;
	}

	class ProducerClass
		: public CraftClass
	{
	public:
		static ProducerClassPtr create( types::GameObjectClass* ptr );
		void setitem( int index, GameObjectClassPtr obj );
	protected:
		explicit ProducerClass( types::ProducerClass* producer );
	private:
		types::ProducerClass* getProducerClass() const;
	};

	void producerclass_register( lua_State* state );
}
