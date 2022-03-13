#pragma once

#include "Missile_Internal.h"

namespace mmm
{
	namespace types { struct PhotonTorpedo; }

	class PhotonTorpedo
		: public Missile
	{
	public:
		static PhotonTorpedoPtr create( types::Entity* entity );
		virtual	~PhotonTorpedo(){};
		ST3D_Colour getPhotonColour() const;
		void		setPhotonColour( const ST3D_Colour& colour );
	protected:
		explicit	   PhotonTorpedo( types::PhotonTorpedo* torpedo );
		virtual void   allocateReplacement( luabind::detail::object_rep* object );
	private:
		types::PhotonTorpedo* getPhotonTorpedo() const;
	};

	void photontorpedo_register( lua_State* state );
}
