#include "ResearchPod_Internal.h"
#include "Craft_Internal.h"
#include "Type_ResearchPod.h"
#include "Type_ResearchStation.h"

namespace mmm
{
	ResearchPodPtr 
	ResearchPod::create( types::Entity* entity )
	{
		return ResearchPodPtr( new ResearchPod( static_cast<types::ResearchPod*>( entity ) ) );
	}

	ResearchPod::ResearchPod( types::ResearchPod* pod )
		: Craft( pod )
	{

	}

	void
	ResearchPod::allocateReplacement( luabind::detail::object_rep* obj )
	{
		entity_allocate_replacement<Craft>( obj, boost::static_pointer_cast<Craft>( shared_from_this() ) );
	}

	EntityPtr	
	ResearchPod::getStation() const
	{
		return createEntityPtr( getResearchPod()->researchStation );
	}

	types::ResearchPod* 
	ResearchPod::getResearchPod() const
	{
		return static_cast<types::ResearchPod*>( getEntity() );
	}
}
