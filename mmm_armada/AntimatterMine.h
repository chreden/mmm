#pragma once

#include "Mine.h"

namespace mmm
{
	namespace types { struct AntimatterMine; }

	class AntimatterMine
		: public Mine
	{
	public:
		static AntimatterMinePtr create( types::Entity* entity );
	protected:
		explicit AntimatterMine( types::AntimatterMine* antimatterMine );
		virtual void allocateReplacement( luabind::detail::object_rep* obj );
	private:
		types::AntimatterMine* getAntimatterMine() const;
	};

	void antimattermine_register( lua_State* state );
}