#pragma once

#include "EntityFinderFilter.h"

namespace mmm
{
	class EntityFinderFilterObject : public EntityFinderFilter
	{
	public:
		explicit EntityFinderFilterObject( luabind::object table, luabind::object function );
		virtual ~EntityFinderFilterObject( );
		virtual bool call( EntityPtr entity );
	private:
		luabind::object table_;
		luabind::object function_;
	};
}
