#include "Scrap_Internal.h"
#include "ScrapClass_Internal.h"
#include "Type_ScrapClass.h"
#include "Type_Scrap.h"

namespace mmm
{
	ScrapPtr
	Scrap::create( types::Entity* entity )
	{
		return ScrapPtr( new Scrap( static_cast<types::Scrap*>( entity ) ) );
	}

	Scrap::Scrap( types::Scrap* scrap )
		: TerrainObject( scrap )
	{

	}

	GameObjectClassPtr 
	Scrap::getClass() const
	{
		return GameObjectClassPtr( new ScrapClass( static_cast<types::ScrapClass*>( getGameObject()->m_class ) ) );
	}

	void
	Scrap::allocateReplacement( luabind::detail::object_rep* obj )
	{
		entity_allocate_replacement<Scrap>( obj, boost::static_pointer_cast<Scrap>( shared_from_this() ) );
	}
}