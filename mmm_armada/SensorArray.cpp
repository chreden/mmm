#include "SensorArray.h"
#include "Type_SensorArray.h"

namespace mmm
{
	SensorArrayPtr
	SensorArray::create( types::Entity* entity )
	{
		return SensorArrayPtr( new SensorArray( static_cast<types::SensorArray*>( entity ) ) );
	}

	SensorArray::SensorArray( types::SensorArray* sensor )
		: Craft( sensor )
	{

	}

	void
	SensorArray::allocateReplacement( luabind::detail::object_rep* object )
	{
		entity_allocate_replacement<SensorArray>( object, boost::static_pointer_cast<SensorArray>( shared_from_this() ) );
	}
}
