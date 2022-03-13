#include "ProducerClass_Internal.h"
#include "Type_ProducerClass.h"

namespace mmm
{
	ProducerClassPtr 
	ProducerClass::create( types::GameObjectClass* ptr )
	{
		return ProducerClassPtr( new ProducerClass( static_cast<types::ProducerClass*>( ptr ) ) );
	}

	ProducerClass::ProducerClass( types::ProducerClass* producer )
		: CraftClass( producer )
	{
			
	}

	types::ProducerClass*
	ProducerClass::getProducerClass() const
	{
		return static_cast<types::ProducerClass*>( getClass() );
	}

	void 
	ProducerClass::setitem( int index, GameObjectClassPtr obj )
	{
		//This is only done when fleetops is present. We need to make sure that
		//we detect FO.
		types::GameObjectClass*** redirect = reinterpret_cast<types::GameObjectClass***>( getProducerClass()->buildItem );
		types::GameObjectClass** items = *redirect;
		items[index] = obj->getClass();
	}
}
