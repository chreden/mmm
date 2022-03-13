#include "PhotonTorpedo_Internal.h"
#include "Type_PhotonTorpedo.h"


namespace mmm
{
	PhotonTorpedoPtr
	PhotonTorpedo::create( types::Entity* entity )
	{
		return PhotonTorpedoPtr( new PhotonTorpedo( static_cast<types::PhotonTorpedo*>( entity ) ) );
	}

	PhotonTorpedo::PhotonTorpedo( types::PhotonTorpedo* torpedo )
		: Missile( torpedo )
	{

	}

	ST3D_Colour 
	PhotonTorpedo::getPhotonColour() const
	{
		return getPhotonTorpedo()->m_photonColor;
	}

	void		
	PhotonTorpedo::setPhotonColour( const ST3D_Colour& colour )
	{
		getPhotonTorpedo()->m_photonColor = colour;
	}

	types::PhotonTorpedo*
	PhotonTorpedo::getPhotonTorpedo() const
	{
		return static_cast<types::PhotonTorpedo*>( getEntity() );
	}

	void
	PhotonTorpedo::allocateReplacement( luabind::detail::object_rep* obj )
	{
		entity_allocate_replacement<PhotonTorpedo>( obj, boost::static_pointer_cast<PhotonTorpedo>( shared_from_this() ) );
	}
}
