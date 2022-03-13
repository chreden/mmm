#include "BeamToggle.h"
#include "Type_BeamToggle.h"

namespace mmm
{
	BeamTogglePtr
	BeamToggle::create( types::Entity* entity )
	{
		return BeamTogglePtr( new BeamToggle( static_cast<types::BeamToggle*>( entity ) ) );
	}

	BeamToggle::BeamToggle( types::BeamToggle* beamToggle )
		: Ordnance( beamToggle )
	{

	}

	void
	BeamToggle::allocateReplacement( luabind::detail::object_rep* obj )
	{
		entity_allocate_replacement<BeamToggle>( obj, boost::static_pointer_cast<BeamToggle>( shared_from_this() ) );
	}

	types::BeamToggle*
	BeamToggle::getBeamToggle() const
	{
		return static_cast<types::BeamToggle*>( getEntity() );
	}

	Vector3
	BeamToggle::getStartPosition() const
	{
		return getBeamToggle()->startPos;
	}

	Vector3
	BeamToggle::getEndPosition() const
	{
		return getBeamToggle()->endPos;
	}

	void
	BeamToggle::setStartPosition( const Vector3& position )
	{
		getBeamToggle()->startPos = position;
	}

	void
	BeamToggle::setEndPosition( const Vector3& position )
	{
		getBeamToggle()->endPos = position;
	}
}
