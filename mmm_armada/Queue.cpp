#include "Queue.h"
#include "QueueType.h"
#include "Entity_Internal.h"
#include "Type_Craft.h"

namespace mmm
{
	namespace
	{
		const std::size_t Function_Remove = 0x00537800;
	}

	Queue::Queue( types::Queue* queue )
		: queue_( queue )
	{

	}

	types::Queue* 
	Queue::getQueue() const
	{
		return queue_;
	}

	int 
	Queue::getSize() const
	{
		return queue_->m_idList.size();
	}

	luabind::object 
	Queue::getEntries() const
	{
		luabind::object results = luabind::newtable(common::Storage::instance().mainLuaVM);
		for( int i = 0; i < queue_->m_idList.size(); ++i )
		{
			results[ i + 1 ] = createEntityPtr( GetEntity<types::Entity>( queue_->m_idList.at( i ) ) );
		}
		return results;
	}

	const Vector3	
	Queue::getOffset() const
	{
		return queue_->m_offset;
	}

	//?remove@QueueManager@@QAEXPAVCraft@@@Z 00537800
	//thiscall void QueueManager::remove( types::Craft* craft ) @ 0x00537800

	void			
	Queue::remove( EntityPtr entity )
	{
		if( entity->isType( Entity_Craft ) )
		{
			types::Craft* craft = static_cast<types::Craft*>( entity->getEntity() );
			(getQueue()->*memory_function<void (types::Queue::*)(types::Craft*)>( Function_Remove ))
				( craft );
		}
	}
}
