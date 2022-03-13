#include "PhotonTorpedo_Internal.h"

namespace mmm
{
	void
	photontorpedo_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<PhotonTorpedo, Missile, EntityPtr>( "PhotonTorpedo" )
				.property( "color", &PhotonTorpedo::getPhotonColour, &PhotonTorpedo::setPhotonColour)
		];
	}
}
