#include "EntityFinder.h"
#include "ScriptErrors.h"
#include "Entities_Internal.h"

#include "EntityFinderFilterFunction.h"
#include "EntityFinderFilterObject.h"

namespace mmm
{
	EntityFinder::EntityFinder( )
	{

	}

	EntityFinder::EntityFinder( luabind::object filters )
	{
		if( LUA_TTABLE == luabind::type( filters ) )
		{
			for( luabind::raw_iterator i( filters ), end; 
					i != end;
					++i )
			{
				if( LUA_TUSERDATA == luabind::type( *i ) )
				{
					luabind::object func = (*i)["evaluate"];
					if( func.is_valid() && luabind::type( func ) == LUA_TFUNCTION )
					{
						filters_.push_back( EntityFinderFilterPtr( new EntityFinderFilterObject( *i, func ) ) );
					}
				}
				else if( LUA_TFUNCTION == luabind::type( *i ) )
				{
					filters_.push_back( EntityFinderFilterPtr( new EntityFinderFilterFunction( *i ) ) );
				}
			}
		}
		else if( LUA_TFUNCTION == luabind::type( filters ) )
		{
			//Has to be a function - at least, we will only accept a function
			//here.
			filters_.push_back( EntityFinderFilterPtr( new EntityFinderFilterFunction( filters ) ) );
		}
		else if( LUA_TUSERDATA == luabind::type( filters ) )
		{
			//For each thing we must check to see what it is.
			luabind::object eval = filters["evaluate"];
			if( eval.is_valid() && luabind::type( eval ) == LUA_TFUNCTION )
			{
				//We have an object
				filters_.push_back( EntityFinderFilterPtr( new EntityFinderFilterObject( filters, eval ) ) );
			}
		}
	}

	luabind::object 
	EntityFinder::find( ) const
	{
		std::vector<EntityPtr> results;
		innerFind( results );

		luabind::object luaResults = luabind::newtable( common::Storage::instance().mainLuaVM );
			
		const std::size_t Count = results.size();
		for( std::size_t e = 0;
				e < Count;
				++e )
		{
			luaResults[e+1] = results[e];
		}

		return luaResults;
	}
	
	luabind::object		
	EntityFinder::find( int max ) const
	{
		std::vector<EntityPtr> results;
		innerFind( results, max );
		luabind::object luaResults = luabind::newtable( common::Storage::instance().mainLuaVM );
		const std::size_t Count = results.size();
		for( std::size_t e = 0;
				e < Count;
				++e )
		{
			luaResults[e+1] = results[e];
		}
		return luaResults;
	}

	EntityPtr
	EntityFinder::findOne( ) const
	{
		std::vector<EntityPtr> results;
		innerFind( results, 1 );
		if( results.empty() )
		{
			return EntityPtr();
		}
		return results[0];
	}

	void 
	EntityFinder::innerFind( std::vector<EntityPtr>& results, int max ) const
	{
		lua_State* state = common::Storage::instance().mainLuaVM;

		std::vector<EntityPtr> entities;
		Entities::getActiveEntities( entities );


		const std::size_t Count = entities.size();
		const std::size_t FilterCount = filters_.size();
		for( int e = 0; e < Count; ++e )
		{
			EntityPtr entity = entities[e];

			//Don't use expired things because it causes trouble.
			if( entity->expired() )
			{
				continue;
			}

			bool passes = true;

			//Check all filters.
			for( std::size_t f = 0; f < FilterCount; ++f )
			{
				try
				{
					if( !filters_[f]->call(entity) )
					{
						passes = false;
						break;
					}
				}
				catch( const luabind::error& )
				{
					scriptError( std::string("Error in evaluate : ") + lua_tostring( state, -1 ) );
				}
			}

			if( passes )
			{
				results.push_back( entity );
				if( max != -1 && results.size() == static_cast<std::size_t>( max ) )
				{
					return;
				}
			}
		}
	}
}
