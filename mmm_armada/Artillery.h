#pragma once

#include "Bullet.h"

namespace mmm
{
	namespace types { struct Artillery; }

	class Artillery
		: public Bullet
	{
	public:
		static ArtilleryPtr create( types::Entity* entity );

		ST3D_Colour getArtilleryColor() const;
		void		setArtilleryColor( const ST3D_Colour& color );
	protected:
		explicit Artillery( types::Artillery* artillery );

		virtual void allocateReplacement( luabind::detail::object_rep* obj );
	private:
		types::Artillery* getArtillery() const;
	};

	void artillery_register( lua_State* state );
}
