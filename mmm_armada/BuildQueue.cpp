#include "BuildQueue.h"
#include "Type_Producer.h"
#include "GameObjectClass_Internal.h"

namespace mmm
{
	namespace
	{
		const std::size_t Address_ClearBuildQueue	 = 0x004b78c0;
		const std::size_t Address_PushBuildQueueItem = 0x004b7930;
		const std::size_t Address_PopBuildQueueItem	 = 0x004b79b0;
		const std::size_t Address_IsBuildListEmpty	 = 0x004b7b60;
		const std::size_t Address_GetBuildQueueSize	 = 0x004b7b70;
		const std::size_t Address_StartBuild		 = 0x004b8180;
		const std::size_t Address_RemoveItem		 = 0x004b7a10;

		void
		producer_clearBuildQueue( types::Producer* producer )
		{
			(producer->*memory_function< void ( types::Producer::* ) ( ) >( Address_ClearBuildQueue ))();
		}

		bool
		producer_pushBuildQueue( types::Producer* producer, const std::string& odf )
		{
			GameObjectClass* gameClass = static_cast<GameObjectClass*>(FindGameObjectClass( odf.c_str( ) ));
			if( gameClass )
			{
				(producer->*memory_function<void (types::Producer::*)(GameObjectClass*)>(Address_PushBuildQueueItem))(gameClass);
				return true;
			}
			return false;
		}

		void
		producer_popBuildQueue( types::Producer* producer )
		{
			(producer->*memory_function<void (types::Producer::*)()>(Address_PopBuildQueueItem))();
		}

		bool
		producer_isBuildQueueEmpty( types::Producer* producer )
		{
			return (producer->*memory_function< bool (types::Producer::*)() >( Address_IsBuildListEmpty ))();
		}

		int
		producer_getBuildQueueSize( types::Producer* producer )
		{
			return (producer->*memory_function< int (types::Producer::*)() >( Address_GetBuildQueueSize ))();
		}

		void
		producer_completeBuildItem( types::Producer* producer )
		{
			if( !producer_isBuildQueueEmpty( producer ) )
			{
				producer->m_buildDoneTime = 0;
				(producer->*memory_function<bool (types::Producer::*)() >( Address_StartBuild ))();
			}
		}

		void
		producer_removeBuildQueueItem( types::Producer* producer, int index )
		{
			(producer->*memory_function< void (types::Producer::*)( int ) >( Address_RemoveItem ))( index );
		}
	}

	BuildQueuePtr
	BuildQueue::create( ProducerPtr producer )
	{
		return BuildQueuePtr( new BuildQueue( producer ) );
	}

	BuildQueue::BuildQueue( ProducerPtr producer )
		: producer_( producer )
	{

	}

	void
	BuildQueue::clear( )
	{
		producer_clearBuildQueue( producer_->getProducer() );
	}

	bool
	BuildQueue::push( const std::string& odf )
	{
		return producer_pushBuildQueue( producer_->getProducer(), odf );
	}

	void
	BuildQueue::pop( )
	{
		return producer_popBuildQueue( producer_->getProducer() );
	}

	void
	BuildQueue::complete( )
	{
		producer_completeBuildItem( producer_->getProducer() );
	}

	int
	BuildQueue::getSize( ) const
	{
		return producer_getBuildQueueSize( producer_->getProducer() );
	}

	luabind::object
	BuildQueue::getItems( ) const
	{
		luabind::object results = luabind::newtable( common::Storage::instance().mainLuaVM );
		types::BuildQueueItem* item = producer_->getProducer()->m_pBuildQueue;
		int					   i	= 1;
		while( item )
		{
			results[i++] = createGameObjectClassPtr( item->m_next_obj );;
			item = item->m_next;
		}
		return results;
	}

	bool
	BuildQueue::isEmpty( ) const
	{
		return producer_isBuildQueueEmpty( producer_->getProducer() );
	}

	void
	BuildQueue::remove( int index )
	{
		return producer_removeBuildQueueItem( producer_->getProducer(), index - 1 );
	}

	float
	BuildQueue::getTimeRemaining( ) const
	{
		return producer_->getProducer()->m_buildDoneTime;
	}
}
