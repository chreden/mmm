#include "Phaser_Internal.h"
#include "Type_Phaser.h"

namespace mmm
{
	PhaserPtr
	Phaser::create( types::Entity* entity )
	{
		return PhaserPtr( new Phaser( static_cast<types::Phaser*> ( entity ) ) );
	}

	Phaser::Phaser( types::Phaser* phaser )
		: Beam( phaser )
	{

	}

	ST3D_Colour 
	Phaser::getPhaserColour() const
	{
		return getPhaser()->m_phaserColor;
	}

	void		
	Phaser::setPhaserColour( const ST3D_Colour& colour )
	{
		getPhaser()->m_phaserColor = colour;
	}


	types::Phaser*
	Phaser::getPhaser() const
	{
		return static_cast<types::Phaser*>( getEntity() );
	}

	void
	Phaser::allocateReplacement( luabind::detail::object_rep* obj )
	{
		entity_allocate_replacement<Phaser>( obj, boost::static_pointer_cast<Phaser>( shared_from_this() ) );
	}
}
