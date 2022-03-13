#include "Producer.h"
#include "Type_Producer.h"
#include "Type_Entity.h"
#include "GameObject_Internal.h"
#include "ProducerClass_Internal.h"
#include "Type_ProducerClass.h"
#include "Type_ResearchStation.h"
#include "BuildQueue.h"

namespace mmm
{
	namespace
	{
		const std::size_t Address_GetBuildObjectTime = 0x004b7cd0;
	}

	ProducerPtr 
	Producer::create( types::Entity* entity )
	{
		return ProducerPtr( new Producer( static_cast<types::Producer*>( entity ) ) );
	}

	Producer::Producer( types::Producer* producer )
		: Craft( producer )
	{

	}

	types::Producer*
	Producer::getProducer( ) const
	{
		return static_cast<types::Producer*>( getEntity() );
	}

	BuildQueuePtr
	Producer::getBuildQueue() const
	{
		return BuildQueue::create( boost::static_pointer_cast<Producer>( boost::const_pointer_cast<Entity>( shared_from_this() ) ) );
	}

	EntityPtr
	Producer::getLastBuilt( ) const
	{
		return createEntityPtr( GetEntity<types::Entity>( getProducer()->m_previousShipBuilt ) );
	} 

	float 
	Producer::getBuildObjectTime( ) const
	{
		typedef float (types::Producer::*MemFunction) ( );
		MemFunction function = memory_function< MemFunction >( Address_GetBuildObjectTime );
		return (getProducer()->*function)( );
	}

	void 
	Producer::allocateReplacement( luabind::detail::object_rep* obj )
	{
		entity_allocate_replacement<Producer>( obj, boost::static_pointer_cast<Producer>(shared_from_this()) );	
	}
}
