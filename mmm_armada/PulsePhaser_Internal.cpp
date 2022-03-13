#include "PulsePhaser_Internal.h"
#include "Type_PulsePhaser.h"

namespace mmm
{
	PulsePhaserPtr 
	PulsePhaser::create( types::Entity* entity )
	{
		return PulsePhaserPtr( new PulsePhaser( static_cast<types::PulsePhaser*>( entity ) ) );
	}

	PulsePhaser::PulsePhaser( types::PulsePhaser* pulsePhaser )
		: Bullet( pulsePhaser )
	{

	}

	ST3D_Colour 
	PulsePhaser::getPhaserColour() const
	{
		return getPulsePhaser()->m_phaserColour;
	}

	void		
	PulsePhaser::setPhaserColour( const ST3D_Colour& colour )
	{
		getPulsePhaser()->m_phaserColour = colour;
	}

	types::PulsePhaser* 
	PulsePhaser::getPulsePhaser( ) const
	{
		return static_cast<types::PulsePhaser*>( getEntity() );
	}

	void
	PulsePhaser::allocateReplacement( luabind::detail::object_rep* obj )
	{
		entity_allocate_replacement<PulsePhaser>( obj, boost::static_pointer_cast<PulsePhaser>( shared_from_this() ) );
	}
}
