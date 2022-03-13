#include "MiningStationClass_Internal.h"
#include "Type_MiningStationClass.h"

namespace mmm
{
	MiningStationClass::MiningStationClass( types::MiningStationClass* station )
		: ProducerClass( station )
	{

	}

	types::MiningStationClass*
	MiningStationClass::getMiningStationClass() const
	{
		return static_cast<types::MiningStationClass*>( getClass() );
	}
}