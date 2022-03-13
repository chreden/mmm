#pragma once

#include "Types.h"
#include "EntityHook.h"

namespace mmm
{
	namespace types
	{
		struct Entity;
	}

	class EntityReference
	{
	public:
		enum State
		{
			Inactive = 0,
			Active
		};

		static EntityReferencePtr create( int id );
		static EntityReferencePtr create( types::Entity* ent );
		
								~EntityReference();
		State					getState() const;
		types::Entity*			getEntity() const;
		
		bool					hasHooks( ) const;

		bool					addHook( const std::string& id, EntityHook::Type type, luabind::object table, 
			luabind::object, luabind::object argument );

		bool					unhook( const std::string& id );

		bool					unhook( HookPtr hook );

		luabind::object			getHooks( ) const;
			
		void					setID( int id );

		static void				updateReferences();
		static void				destroyReferences();
	private:
		static EntityReferencePtr find( int id );

		explicit				EntityReference( int id );
		explicit				EntityReference( types::Entity* ent );

		void callHook( EntityHook::Type type ) const;

		void		 update();
		EntityID	 entityID_;
		State		 state_;

		std::unordered_map<std::string, EntityHookPtr> hooks_;
	};
}
