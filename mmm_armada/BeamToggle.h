#pragma once

#include "Ordnance.h"

namespace mmm
{
	namespace types { struct BeamToggle; }

	class BeamToggle
		: public Ordnance
	{
	public:
		static BeamTogglePtr create( types::Entity* entity );
		Vector3 getStartPosition() const;
		Vector3 getEndPosition() const;

		void setStartPosition( const Vector3& position );
		void setEndPosition( const Vector3& position );

	protected:
		explicit BeamToggle( types::BeamToggle* beamToggle );
		virtual void allocateReplacement( luabind::detail::object_rep* obj );
	private:
		types::BeamToggle* getBeamToggle() const;
	};

	void beamtoggle_register( lua_State* state );
}
