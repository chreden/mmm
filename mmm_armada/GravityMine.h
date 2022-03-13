#pragma once

#include "Mine.h"

namespace mmm
{
	namespace types { struct GravityMine; }
	
	class GravityMine
		: public Mine
	{
	public:
		static GravityMinePtr create( types::Entity* entity );
	protected:
		explicit GravityMine( types::GravityMine* gravityMine );
		virtual void allocateReplacement( luabind::detail::object_rep* obj );
	private:
		types::GravityMine* getGravityMine() const;
	};

	void gravitymine_register( lua_State* state );
}
