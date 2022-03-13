#include "OrdnanceDamage.h"
#include "OrdnanceType.h"

namespace mmm
{
	OrdnanceDamagePtr
	OrdnanceDamage::create( types::Ordnance* ordnance )
	{
		return OrdnanceDamagePtr( new OrdnanceDamage( ordnance ) );
	}

	OrdnanceDamage::OrdnanceDamage( types::Ordnance* ordnance )
		: ordnance_( ordnance )
	{

	}

	float
	OrdnanceDamage::getTotal() const
	{
		return ordnance_->stDamage.total;
	}

	Special
	OrdnanceDamage::getFlags( ) const
	{
		return ordnance_->stDamage.flags;
	}

	void
	OrdnanceDamage::setTotal( float value )
	{
		ordnance_->stDamage.total = value;
	}

	void
	OrdnanceDamage::setFlags( Special value )
	{
		ordnance_->stDamage.flags = value;
	}
}
