#include "Beam_Internal.h"
#include "Type_Beam.h"

namespace mmm
{
	BeamPtr
	Beam::create( types::Entity* entity )
	{
		return BeamPtr( new Beam( static_cast<types::Beam*>( entity ) ) );
	}

	Beam::Beam( types::Beam* beam )
		: Ordnance( beam )
	{

	}

	types::Beam*
	Beam::getBeam() const
	{
		return static_cast<types::Beam*>( getEntity() );
	}

	void
	Beam::allocateReplacement( luabind::detail::object_rep* obj )
	{
		entity_allocate_replacement<Beam>( obj, boost::static_pointer_cast<Beam>( shared_from_this() ) );
	}

	Vector3
	Beam::getStartPos() const
	{
		return getBeam()->m_startPos;
	}

	Vector3
	Beam::getEndPos() const
	{
		return getBeam()->m_endPos;
	}
}
