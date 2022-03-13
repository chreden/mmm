#include "EntityReference.h"
#include "ScriptErrors.h"
#include "Entity_Internal.h"
#include "Type_Entity.h"

namespace mmm
{
	namespace
	{
		std::list<EntityReferencePtr> entityReferences;

        const std::size_t Address_GetEntity = 0x004cfff0;
	}

	EntityReferencePtr 
	EntityReference::create( int id )
	{
		EntityReferencePtr ptr = find( id );
		if( !ptr )
		{
			ptr = EntityReferencePtr( new EntityReference( id ) );
			entityReferences.push_back( ptr );
		}
		return ptr;
	}
	
	EntityReferencePtr 
	EntityReference::create( types::Entity* ent )
	{
		if( !ent )
		{
			return EntityReferencePtr();
		}
		return create( ent->m_entity_id );
	}

	EntityReference::EntityReference( int id )
		: entityID_( createEntityID( id ) ), state_( Active )
	{
		update();
	}

	EntityReference::EntityReference( types::Entity* ent )
		: state_( Active )
	{
		if( ent )
		{
			entityID_ = createEntityID( ent->m_entity_id );
		}
	}

	EntityReference::~EntityReference( )
	{

	}

	void
	EntityReference::setID( int id )
	{
		callHook( EntityHook::OnReplace );
		entityID_.m_id = id;
	}

	EntityReference::State		 
	EntityReference::getState() const
	{
		return state_;
	}

	types::Entity*
	EntityReference::getEntity( ) const
	{
		if( state_ == Inactive )
		{
			return 0;
		}
		return reinterpret_cast<types::Entity*(*)(int)>( Address_GetEntity )( entityID_.m_id );
	}

	void
	EntityReference::update( )
	{
		//Only update the reference if we are active - if we have been
		//deactivated we just stay as we are.
		if( state_ == Active )
		{
			types::Entity* ent = 
				reinterpret_cast<types::Entity*(*)(int)>( Address_GetEntity )( entityID_.m_id );
				
			if( 0 == ent )
			{
				if( !common::Storage::instance().fleetops )
				{
					callHook( EntityHook::OnDestroy );
					state_ = Inactive;
				}
				else
				{
					EntityID newID = createEntityID( getScriptInterface()->GetReplacementChild( entityID_.m_id ) );
					if( newID.m_id == 0 )
					{
						callHook( EntityHook::OnDestroy );
						state_ = Inactive;
						return;
					}

					//Fine, our entity has been replaced so we will use this new ID.
					entityID_ = newID;

					//Inform the user via hook interface
					callHook( EntityHook::OnReplace );
				}
			}
		}
	}

	void 
	EntityReference::callHook( EntityHook::Type type ) const
	{
		//Target entity (the entity we're managing).
		EntityPtr entity = createEntityPtr( getEntity() );

		//Similar to updating the monitors, we take a copy of the hooks
		//here so they can be removed during updating.
		auto hooksCopy = hooks_;
		for( auto hookIter = hooksCopy.begin(); hookIter != hooksCopy.end(); ++hookIter )
		{
			EntityHookPtr hook = hookIter->second;
			if( hook && hook->getType() == type )
			{
				try
				{
					if( hook->getTable().is_valid() && hook->getTable() )
					{
						luabind::call_function<void>( hook->getFunction(), hook->getTable(), entity, hook );
					}
					else
					{
						luabind::call_function<void>( hook->getFunction(), entity, hook );
					}
				}
				catch ( luabind::error& ) 
				{
					scriptError( std::string( "Error in Entity Hook (" + hook->getId() + ") : " ) + lua_tostring(common::Storage::instance().mainLuaVM, -1) );
				}
			}
		}
	}

	bool					
	EntityReference::hasHooks( ) const
	{
		return !hooks_.empty();
	}

	bool
	EntityReference::addHook( const std::string& id, EntityHook::Type type, luabind::object table, luabind::object function, luabind::object argument )
	{
		if( hooks_.find( id ) != hooks_.end() )
		{
			return false;
		}
		hooks_[id] = EntityHookPtr( new EntityHook( id, type, table, function, argument ) );
		return true;
	}

	bool
	EntityReference::unhook( const std::string& id )
	{
		auto iter = hooks_.find( id );
		if( iter == hooks_.end( ) )
		{
			return false;
		}
		hooks_.erase( iter );
		return true;
	}

	bool
	EntityReference::unhook( HookPtr hook )
	{
		auto iter = std::find_if( hooks_.begin(), hooks_.end(),
			[&](const std::pair<std::string, EntityHookPtr>& hookIter)
				{
					return hookIter.second == hook;
				} );
		if( iter == hooks_.end() )
		{
			return false;
		}
		hooks_.erase( iter );
		return true;
	}

	luabind::object 
	EntityReference::getHooks() const
	{
		luabind::object results = luabind::newtable( common::Storage::instance().mainLuaVM );
		for( auto iter = hooks_.begin();
			 iter != hooks_.end();
			 ++iter )
		{
			results[iter->first] = HookPtr( iter->second );
		}
		return results;
	}

	EntityReferencePtr	
	EntityReference::find( int id )
	{
		for( std::list<EntityReferencePtr>::iterator iter = entityReferences.begin();
				iter != entityReferences.end();
				++iter )
		{
			if( (*iter)->getEntity() &&
				(*iter)->getEntity()->m_entity_id == id &&
				(*iter)->getState() == Active )
			{
				return (*iter);
			}
		}
		return EntityReferencePtr();
	}

	void 
	EntityReference::updateReferences()
	{
		std::vector<EntityReferencePtr> toRemove;

		for( std::list<EntityReferencePtr>::iterator iter = entityReferences.begin();
				iter != entityReferences.end();
				++iter )
		{
			(*iter)->update();
			if( (*iter)->getState() == Inactive )
			{
				toRemove.push_back( *iter );
			}
		}

		for( std::size_t i = 0; i < toRemove.size(); ++i )
		{
			entityReferences.remove( toRemove[i] );
		}
	}
}
