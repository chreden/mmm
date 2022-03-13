#pragma once

#include "Craft_Internal.h"

namespace mmm
{
	namespace types { class Producer; }

	class Producer
		: public Craft
	{
	public:
		static ProducerPtr create( types::Entity* entity );

		EntityPtr getLastBuilt() const;

		BuildQueuePtr getBuildQueue() const;

		float	getBuildObjectTime() const;

		types::Producer* getProducer() const;
	protected:
		explicit Producer( types::Producer* producer );
		void allocateReplacement( luabind::detail::object_rep* obj );
	};
	
	void producer_register( lua_State* state );
}
