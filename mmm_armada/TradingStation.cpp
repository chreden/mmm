#include "TradingStation.h"
#include "TradingStationClass_Internal.h"
#include "Type_TradingStation.h"
#include "Type_TradingStationClass.h"

namespace mmm
{
	TradingStationPtr
	TradingStation::create( types::Entity* entity )
	{
		return TradingStationPtr( new TradingStation( static_cast<types::TradingStation*>( entity ) ) );
	}

	TradingStation::TradingStation( types::TradingStation* station )
		: MiningStation( station )
	{

	}

	void
	TradingStation::allocateReplacement( luabind::detail::object_rep* object )
	{
		entity_allocate_replacement<TradingStation>( object, boost::static_pointer_cast<TradingStation>( shared_from_this() ) );
	}

	types::TradingStation*
	TradingStation::getTradingStation() const
	{
		return static_cast<types::TradingStation*>( getEntity() );
	}

	GameObjectClassPtr 
	TradingStation::getClass() const
	{
		return GameObjectClassPtr( new TradingStationClass( static_cast<types::TradingStationClass*>( getTradingStation()->m_class ) ) );
	}

	eDockingState 
	TradingStation::getDockingState() const
	{
		return getTradingStation()->m_DockingState;
	}

	Vector3
	TradingStation::getRallyPoint() const
	{
		return getTradingStation()->m_rallyPoint;
	}

	EntityPtr 
	TradingStation::getDockedFerengi() const
	{
		return createEntityPtr( GetEntity<types::Entity>( getTradingStation()->m_ferengiNowTradingHandle ) );
	}

	void
	TradingStation::setRallyPoint( const Vector3& rallyPoint )
	{
		getTradingStation()->m_rallyPoint = rallyPoint;
	}
}