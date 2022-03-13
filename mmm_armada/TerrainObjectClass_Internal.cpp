#include "TerrainObjectClass_Internal.h"
#include "Type_TerrainObjectClass.h"

namespace mmm
{
	TerrainObjectClass::TerrainObjectClass( types::TerrainObjectClass* object )
		: GameObjectClass( object )
	{

	}

	types::TerrainObjectClass*
	TerrainObjectClass::getTerrainObjectClass() const
	{
		return static_cast<types::TerrainObjectClass*>( getClass() );
	}
}
