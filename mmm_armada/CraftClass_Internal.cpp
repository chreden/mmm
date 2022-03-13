#include "CraftClass_Internal.h"
#include "Type_CraftClass.h"

namespace mmm
{
	CraftClassPtr 
	CraftClass::create( types::GameObjectClass* ptr )
	{
		return CraftClassPtr( new CraftClass( static_cast<types::CraftClass*>( ptr ) ) );
	}

	CraftClass::CraftClass( types::CraftClass* craftClass )
		: GameObjectClass( craftClass )
	{

	}

	types::CraftClass* 
	CraftClass::getCraftClass() const
	{
		return static_cast<types::CraftClass*>( getClass() );
	}
}