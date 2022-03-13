#include "Producer.h"
#include "BuildQueue.h"

namespace mmm
{
	void
	producer_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<Producer, Craft, EntityPtr>( "Producer" )
				.property( "buildQueue", &Producer::getBuildQueue )
				.property( "lastBuilt", &Producer::getLastBuilt )
				.property( "buildObjectTime", &Producer::getBuildObjectTime )
		];
	}
}