#pragma once

#include "Entity_Internal.h"
#include "EntityFinderFilter.h"

namespace mmm
{
	class EntityFinder
	{
	public:
		explicit			EntityFinder( );
		explicit			EntityFinder( luabind::object filters );
		luabind::object		find( ) const;
		luabind::object		find( int max ) const;
		EntityPtr			findOne( ) const;
	private:
		void innerFind( std::vector<EntityPtr>& results, int max = -1 ) const;
		std::vector<std::unique_ptr<EntityFinderFilter>> filters_;
	};

	void entityfinder_register( lua_State* state );
}
