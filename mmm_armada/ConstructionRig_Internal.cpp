#include "ConstructionRig_Internal.h"
#include "Type_ConstructionRig.h"
#include "MemRaider.h"

namespace mmm
{
	ConstructionRigPtr
	ConstructionRig::create( types::Entity* entity )
	{
		return ConstructionRigPtr( new ConstructionRig( static_cast<types::ConstructionRig*>( entity ) ) );
	}

	ConstructionRig::ConstructionRig( types::ConstructionRig* rig )
		: Producer( rig )
	{

	}

	int
	ConstructionRig::getBeesOnboard() const
	{
		types::ConstructionRig* rig = getConstructionRig();
		return getConstructionRig()->m_numberOfBeesOnboard;
	}
		
	EntityPtr
	ConstructionRig::getConstructionObject() const
	{
		return createEntityPtr( GetEntity<types::Entity>( getConstructionRig()->m_constructionObjectID ) );
	}

	//Number of bees is going to have to be a class property since it affects all objects o fthis
	//type.
	void
	ConstructionRig::setBeesOnboard( int value )
	{
		memraider::MrNode( getConstructionRig()->m_class ).set<long>( 0x490, value );
	}

	types::ConstructionRig*
	ConstructionRig::getConstructionRig() const
	{
		return static_cast<types::ConstructionRig*>( getEntity() );
	}

	void
	ConstructionRig::allocateReplacement( luabind::detail::object_rep* object )
	{
		entity_allocate_replacement<ConstructionRig>( object, boost::static_pointer_cast<ConstructionRig>(shared_from_this()) );	
	}
}
