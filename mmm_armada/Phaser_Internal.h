#pragma once

#include "Beam_Internal.h"

namespace mmm
{
	namespace types { struct Phaser; }

	class Phaser
		: public Beam
	{
	public:
		static PhaserPtr create( types::Entity* entity );
		ST3D_Colour getPhaserColour() const;
		void		setPhaserColour( const ST3D_Colour& colour );

	protected:
		explicit Phaser( types::Phaser* phaser );

		virtual void   allocateReplacement( luabind::detail::object_rep* object );
	private:
		types::Phaser* getPhaser() const;
	};

	void phaser_register( lua_State* state );
}