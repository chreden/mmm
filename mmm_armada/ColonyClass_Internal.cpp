#include "ColonyClass_Internal.h"
#include "Type_ColonyClass.h"

namespace mmm
{
	ColonyClassPtr 
	ColonyClass::create( types::GameObjectClass* ptr )
	{
		return ColonyClassPtr( new ColonyClass( static_cast<types::ColonyClass*>( ptr ) ) );
	}

	ColonyClass::ColonyClass( types::ColonyClass* colony )
		: CraftClass( colony )
	{

	}
}
