#include "ResourceTransferInterface.h"
#include "Type_Producer.h"
#include "MiningStation.h"
#include "Starbase_Internal.h"
#include "Type_Starbase.h"
#include "Type_ResourceTransferInterface.h"
#include "MiningStationType.h"
#include "OrientedQueue.h"
#include "OrientedQueueType.h"

namespace mmm
{
	namespace 
	{
		const std::size_t Address_IsShipDocked				   = 0x004d7020;
		const std::size_t Address_GetResourceTransferInterface = 0x0049fda0;

		class ResourceTransferInterfaceCallback
			: public Container::Callback
		{
		public:
			explicit ResourceTransferInterfaceCallback( ResourceTransferInterface* iface )
				: interface_( iface )
			{
			}

			virtual ~ResourceTransferInterfaceCallback( )
			{
			}

			virtual float get( eResource resource ) const
			{
				return interface_->getResourceRate( resource );
			}

			virtual void set( eResource resource, float rate )
			{
				interface_->setResourceRate( resource, rate );
			}
		private:
			ResourceTransferInterface* interface_;
		};
	}

	ResourceTransferInterface::ResourceTransferInterface( types::GameObject* object )
		: object_( object )
	{

	}

	bool
	ResourceTransferInterface::isShipDocked() const
	{
		types::ResourceTransferInterface* const iface = getResourceTransferInterface();
		return (iface->*memory_function< bool (types::ResourceTransferInterface::*)()>( Address_IsShipDocked ))();
	}

	EntityPtr 
	ResourceTransferInterface::getDockedShip() const
	{
		return createEntityPtr( GetEntity<types::Entity>( getResourceTransferInterface()->m_dockedShip ) );
	}

	types::ResourceTransferInterface* 
	ResourceTransferInterface::getResourceTransferInterface() const
	{
		if( types::isMiningStation( object_ ) )
		{
			return static_cast<types::MiningStation*>( object_ )->m_pResourceTransferInterface;
		}
		else if( types::isStarbase( object_ ) )
		{
			return static_cast<types::Starbase*>( object_ )->m_pResourceTransferInterface;
		}
		return 0;
	}

	Container
	ResourceTransferInterface::getResourceRates() const
	{
		return Container( std::shared_ptr<Container::Callback>( new ResourceTransferInterfaceCallback( const_cast<ResourceTransferInterface*>(this)) ) );
	}


	float	  
	ResourceTransferInterface::getResourceRate( eResource res ) const
	{
		return getResourceTransferInterface()->m_pTransferData->m_transferRates[res];
	}

	void	  
	ResourceTransferInterface::setResourceRate( eResource res, float value )
	{
		getResourceTransferInterface()->m_pTransferData->m_transferRates[res] = value;
	}

	OrientedQueuePtr 
	ResourceTransferInterface::getMiningQueue() const
	{
		return OrientedQueue::create( getResourceTransferInterface()->m_mining_queue );
	}
}
