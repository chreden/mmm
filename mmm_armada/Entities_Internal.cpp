#include "Entities_Internal.h"
#include "Entity_Internal.h"
#include "Type_Entity.h"
#include "Type_GameObject.h"
#include "Type_GameObjectClass.h"
#include "Type_Craft.h"
#include "Craft_Internal.h"
#include "ScriptErrors.h"
#include "Team_Internal.h"

namespace mmm
{
	namespace
	{
		const std::size_t Address_EntityPointerManager	= 0x00741000;
		const std::size_t Address_FindGameObjectClass	= 0x004cd370;
		const std::size_t Address_IdentityMatrix		= 0x00769380;
		const std::size_t Address_CreateGameObject		= 0x004cd390;
		const std::size_t Address_GetAiMission			= 0x00401370;
		const std::size_t Address_AttachAiProcess		= 0x0042b910;
	}

	EntityPtr
	Entities::add( const std::string& odf, int team, const Vector3& position )
	{
		typedef types::GameObjectClass* ( *FindFunction )( const char* );
		FindFunction function = memory_function< FindFunction >( Address_FindGameObjectClass );

		//Lowercase the odf filename because armada only accepts lowercase odfs.
		std::string lowerOdf( odf );
		std::transform( lowerOdf.begin(), lowerOdf.end(), lowerOdf.begin(), ::tolower );

		types::GameObjectClass* base = function( lowerOdf.c_str() );
			
		if( !base )
		{
			scriptError( "ODF not found" );
			return EntityPtr();
		}

		Matrix34 mat = *reinterpret_cast<Matrix34*>( Address_IdentityMatrix );
		mat.position = position;

		typedef types::GameObject* (types::GameObjectClass::*Creator)( const Matrix34&, int, int, char* ) const;
		Creator creator = memory_function< Creator >( Address_CreateGameObject );

		types::GameObject* object = (base->*creator)( mat, team, 0, 0 );

		void* aiMission = memory_function< void* (*)() >( Address_GetAiMission )( );

		typedef void* (*func)(void*, types::GameObject*);

		memory_function< func >( Address_AttachAiProcess )( aiMission, object );

		return createEntityPtr( object );
	}

	EntityPtr	
	Entities::add( const std::string& odf, TeamPtr team, const Vector3& position )
	{
		if( !team )
		{
			return EntityPtr();
		}
		return add( odf, team->getNumber(), position );
	}

	void
	Entities::find( std::vector<EntityPtr>& ents, FindComparator comparator, void* argument )
	{
		EntityPointerManager* epm = GetEntityPointerManager( );

		for( int i = 0, entsFound = 0; i < epm->m_active_entities_highest; ++i )
		{
			const EntityPointer& entity = epm->m_entity_pointer[ i ];

			if( entity.m_id.m_used )
			{
				EntityPtr ent = createEntityPtr( entity.m_entity );
				if( comparator( ent , argument ) )
				{
					ents.push_back( ent );
				}
				++entsFound;
			}

			if( entsFound == epm->m_active_entities )
			{
				break;
			}
		}
	}
	
	void 
	Entities::getActiveEntities( std::vector<EntityPtr>& results )
	{
		const EntityPointerManager* const epm = GetEntityPointerManager();
		for( int i = 0; i < epm->m_active_entities_highest; ++i )
		{
			const EntityPointer& entity = epm->m_entity_pointer[ i ];
			if( entity.m_id.m_used )
			{
				results.push_back( createEntityPtr(entity.m_entity) );
			}
		}
	}

	bool 
	Entities::remove( EntityPtr entity )
	{
		if( entity )
		{
			getScriptInterface( )->RemoveObject( entity->getID() );
			return true;
		}
		return false;
	}
}