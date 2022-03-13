#pragma once

#include "Craft_Internal.h"

namespace mmm
{
	namespace types { struct MineArray; }

	class MineArray : public Craft
	{
	public:
		static MineArrayPtr create( types::Entity* mine );

		Vector3			getHome() const;
		EntityPtr		getTarget() const;
		eMineArrayState getState() const;
		void			setHome( const Vector3& value );
	protected:
		virtual void allocateReplacement( luabind::detail::object_rep* object );
	private:
		explicit MineArray( types::MineArray* mine );
		types::MineArray* getMineArray() const;
	};

	void minearray_register( lua_State* state );
}