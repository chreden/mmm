#pragma once

#include "Ordnance.h"

namespace mmm
{
	namespace types { struct Beam; }

	class Beam
		: public Ordnance
	{
	public:
		static BeamPtr create( types::Entity* entity );

		virtual	~Beam(){};
		Vector3 getStartPos() const;
		Vector3 getEndPos() const;
	protected:
		explicit Beam( types::Beam* beam );
		virtual void   allocateReplacement( luabind::detail::object_rep* object );
		types::Beam* getBeam() const;
	};

	void beam_register( lua_State* state );
}
