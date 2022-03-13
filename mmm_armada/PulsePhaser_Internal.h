#pragma once

#include "Bullet.h"

namespace mmm
{
	namespace types { struct PulsePhaser; }

	class PulsePhaser
		: public Bullet
	{
	public:
		static PulsePhaserPtr create( types::Entity* entity );

		ST3D_Colour getPhaserColour() const;
		void		setPhaserColour( const ST3D_Colour& colour );

	protected:
		explicit PulsePhaser( types::PulsePhaser* pulsePhaser );

		virtual void   allocateReplacement( luabind::detail::object_rep* object );
	private:
		types::PulsePhaser* getPulsePhaser() const;

	};

	void pulsephaser_register( lua_State* state );
}
