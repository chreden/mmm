#include "Objectives_Internal.h"

namespace mmm
{
	namespace 
	{
		Objectives objectives;
	}

	void
	objectives_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<Objectives>( "Objectives_" )
				.property( "count", &Objectives::getCount )
				.property( "visible", &Objectives::getShow, &Objectives::setShow )
				.property( "objectives", &Objectives::getObjectiveValues )
				.def( "load", &Objectives::load )
				//.property( "header", &Objectives::getObjectivesHeader, &Objectives::setObjectivesHeader )
				//.property( "summaryTitle", &Objectives::getSummaryTitle, &Objectives::setSummaryTitle )
				//.property( "text", &Objectives::getObjectivesText, &Objectives::setObjectivesText )
				//.property( "title", &Objectives::getObjectivesTitle, &Objectives::setObjectivesTitle )
				//.def( "add", &Objectives::addObjective )
				//.def( "remove", &Objectives::removeObjective )
		];

		globals(state)["Objectives"] = &objectives;
	}
}
