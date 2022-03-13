#pragma once

#include "Ordnance.h"

namespace mmm
{
	namespace types { struct Mine; }

	class Mine
		: public Ordnance
	{
	public:
		static MinePtr create( types::Entity* entity );

		eMineStatus getMineStatus() const;
	protected:
		explicit Mine( types::Mine* mine );
		virtual void allocateReplacement( luabind::detail::object_rep* obj );
	private:
		types::Mine* getMine() const;
	};

	void mine_register( lua_State* state );
}
