#include "BlackHole_Internal.h"
#include "Type_BlackHoleClass.h"
#include "BlackHoleClass_Internal.h"
#include "Type_BlackHole.h"

namespace mmm
{
	BlackHolePtr
	BlackHole::create( types::Entity* entity )
	{
		return BlackHolePtr( new BlackHole( static_cast<types::BlackHole*>( entity ) ) );
	}

	BlackHole::BlackHole( types::BlackHole* type )
		: AreaEffectObject( type )
	{

	}

	GameObjectClassPtr 
	BlackHole::getClass() const
	{
		return GameObjectClassPtr( new BlackHoleClass( static_cast<types::BlackHoleClass*>( getGameObject()->m_class ) ) );
	}

	void
	BlackHole::allocateReplacement( luabind::detail::object_rep* obj )
	{
		entity_allocate_replacement<BlackHole>( obj, boost::static_pointer_cast<BlackHole>( shared_from_this() ) );
	}
}
