#include "ResearchStation.h"
#include "Type_ResearchStation.h"

namespace mmm
{
	ResearchStationPtr
	ResearchStation::create( types::Entity* entity )
	{
		return ResearchStationPtr( new ResearchStation( static_cast<types::ResearchStation*>( entity ) ) );
	}

	ResearchStation::ResearchStation( types::ResearchStation* station )
		: Producer( station )
	{

	}

	void
	ResearchStation::allocateReplacement( luabind::detail::object_rep* object )
	{
		entity_allocate_replacement<ResearchStation>( object, boost::static_pointer_cast<ResearchStation>( shared_from_this() ) );
	}

	types::ResearchStation* 
	ResearchStation::getResearchStation() const
	{
		return static_cast<types::ResearchStation*>( getEntity() );
	}

	luabind::object 
	ResearchStation::getPods() const
	{
		luabind::object			resultsTable = luabind::newtable( common::Storage::instance().mainLuaVM );
		types::ResearchStation* station		 = getResearchStation();
		for( int i = 0; i < station->m_numberOfPods; ++i )
		{
			resultsTable[ i + 1 ] = createEntityPtr( station->m_ppPods[i] );
		}
		return resultsTable;
	}
}
