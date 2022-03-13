#include "Artillery.h"
#include "Type_Artillery.h"

namespace mmm
{
	ArtilleryPtr
	Artillery::create( types::Entity* entity )
	{
		return ArtilleryPtr( new Artillery( static_cast<types::Artillery*>( entity ) ) );
	}

	Artillery::Artillery( types::Artillery* artillery )
		: Bullet( artillery )
	{

	}

	types::Artillery*
	Artillery::getArtillery() const
	{
		return static_cast<types::Artillery*>( getEntity() );
	}

	void
	Artillery::allocateReplacement( luabind::detail::object_rep* obj )
	{
		entity_allocate_replacement<Artillery>( obj, boost::static_pointer_cast<Artillery>( shared_from_this() ) );
	}

	ST3D_Colour
	Artillery::getArtilleryColor( ) const
	{
		return getArtillery()->m_photonColor;
	}

	void
	Artillery::setArtilleryColor( const ST3D_Colour& color )
	{
		getArtillery()->m_photonColor = color;
	}
}