#include "CraftSystem_Internal.h"
#include "Type_CraftSystem.h"

namespace mmm
{
	CraftSystem::CraftSystem( CraftPtr craft, types::CraftSystem* system )
		: craft_( craft ), system_( system )
	{

	}

	bool
	CraftSystem::getActive( ) const
	{
		return system_->active;
	}

	bool
	CraftSystem::getPermanentDisable( ) const
	{
		return system_->permanentDisable;
	}

	float
	CraftSystem::getHitpoints( ) const
	{
		return system_->fHitPoints;
	}

	float
	CraftSystem::getHealth( ) const
	{
		return system_->fHitPoints / static_cast<float>(system_->maxHitPoints);
	}

	long
	CraftSystem::getMaxHitpoints() const
	{
		return system_->maxHitPoints;
	}

	void
	CraftSystem::setActive( bool value )
	{
		system_->active = value;
	}

	void
	CraftSystem::setPermanentDisable( bool value )
	{
		system_->permanentDisable = value;
	}

	void
	CraftSystem::setHitpoints( float value )
	{
		system_->fHitPoints = value;
	}

	void
	CraftSystem::setHealth( float value )
	{
		system_->fHitPoints = static_cast<float>( system_->maxHitPoints ) * value;
	}

	void
	CraftSystem::setMaxHitpoints( long value )
	{
		system_->maxHitPoints = value;
	}
}
