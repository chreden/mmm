#pragma once

#include "Container.h"

namespace mmm
{
	namespace types
	{
		struct ResourceInterface;
		struct GameObject;
	}

	class GameObject;

	class ResourceInterface
	{	
	public:
		explicit ResourceInterface( types::GameObject* gameobject );
		virtual	~ResourceInterface(){ };
		
		bool		getResourceIsInfinite( ) const;
		float		getResourceAmount( eResource resoruce ) const;
		EntityPtr	getOrbitalStation( ) const;
		EntityPtr	getMiner() const;
		int			getLastTimeMined() const;
		Container	getResources() const;

		void	setResourceAmount( eResource resource, float amount );
		void	setResourceIsInfinite( bool value );
		bool	isValid() const;
	private:
		types::ResourceInterface* getInterface() const;
		types::GameObject* gameobject_;
	};

	void resourceinterface_register( lua_State* state );
}