#include "MiningStation.h"
#include "Freighter_Internal.h"
#include "MiningStationClass_Internal.h"
#include "Type_MiningStationClass.h"
#include "MiningStationType.h"
#include "Type_Freighter.h"

namespace mmm
{
	MiningStationPtr 
	MiningStation::create( types::Entity* entity )
	{
		return MiningStationPtr( new MiningStation( static_cast<types::MiningStation*>( entity ) ) );
	}

	MiningStation::MiningStation( types::MiningStation* station )
		: Producer( station ), ResourceTransferInterface( station )
	{

	}

	types::MiningStation*
	MiningStation::getMiningStation( ) const
	{
		return static_cast<types::MiningStation*>( getEntity() );
	}

	FreighterPtr
	MiningStation::buildFreighter( )
	{
		types::Freighter* freighter = (getMiningStation()->*memory_function< types::Freighter* (types::MiningStation::*)()>( Address_BuildFreighter ))();
		if( freighter ) 
		{
			return Freighter::create( freighter );
		}
		return FreighterPtr();
	}

	GameObjectClassPtr 
	MiningStation::getClass() const
	{
		return GameObjectClassPtr( new MiningStationClass( static_cast<types::MiningStationClass*>( getMiningStation()->m_class ) ) );
	}

	void
	MiningStation::allocateReplacement( luabind::detail::object_rep* obj )
	{
		entity_allocate_replacement<MiningStation>( obj, boost::static_pointer_cast<MiningStation>( shared_from_this() ) );
	}
}
