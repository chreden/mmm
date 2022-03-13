#pragma once

#include "Container.h"

namespace mmm
{
	namespace types
	{
		struct ResourceTransferInterface;
		struct GameObject;
	}

	class ResourceTransferInterface
	{
	public:
		explicit  ResourceTransferInterface( types::GameObject* object );
		virtual   ~ResourceTransferInterface() { };
		bool	  isShipDocked( ) const;
		EntityPtr getDockedShip() const;
		Container getResourceRates() const;
		OrientedQueuePtr getMiningQueue() const;
		float	  getResourceRate( eResource res ) const;
		void	  setResourceRate( eResource res, float value );
	private:
		types::ResourceTransferInterface* getResourceTransferInterface() const;
		types::GameObject* object_;
	};

	void resourcetransferinterface_register( lua_State* state );
}
