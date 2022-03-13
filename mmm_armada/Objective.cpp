#include "Objective.h"
#include "Objectives_Internal.h"

namespace mmm
{
	Objective::Objective( int index )
		: index_( index )
	{

	}

	const std::string 
	Objective::getText() const
	{
		return Objectives().getObjective( index_ );
	}

	bool			  
	Objective::getState() const
	{
		return Objectives().getObjectiveState( index_ );
	}

	void			  
	Objective::setState( bool value )
	{
		return Objectives().setObjectiveState( index_, value );
	}

	void
	Objective::setText( const std::string& value )
	{
		return Objectives().setObjective( index_, value );
	}

	void 
	objective_register( lua_State* state )
	{
		using namespace luabind;
		module(state)
		[
			class_<Objective>( "Objective" )
				.property( "text", &Objective::getText, &Objective::setText )
				.property( "state", &Objective::getState, &Objective::setState )
		];
	}
}
