#include "Evolver_Internal.h"

namespace mmm
{
	void
	evolver_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<Evolver, Producer, EntityPtr>( "Evolver" )
				//.property( "evolutionProgress", &Evolver::getEvolutionProgress, &Evolver::setEvolutionProgress )
		];
	}
}
