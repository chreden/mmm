#include "IonStorm_Internal.h"
#include "Type_IonStorm.h"

namespace mmm
{
	IonStormPtr
	IonStorm::create( types::Entity* entity )
	{
		return IonStormPtr( new IonStorm( static_cast<types::IonStorm*>( entity ) ) );
	}

	IonStorm::IonStorm( types::IonStorm* storm )
		: AreaEffectObject( storm )
	{

	}

	types::IonStorm::StormState
	IonStorm::getState( ) const
	{
		return getIonStorm()->m_stormState;
	}

	float
	IonStorm::getTimeLeft( ) const
	{
		return getIonStorm()->m_timeLeft;
	}

	float
	IonStorm::getCurrentScaleCount( ) const
	{
		return getIonStorm()->m_currentScaleCount;
	}

	void
	IonStorm::setState( types::IonStorm::StormState state )
	{
		getIonStorm()->m_stormState = state;
	}

	void
	IonStorm::setTimeLeft( float timeLeft )
	{
		getIonStorm()->m_timeLeft = timeLeft;
	}

	void
	IonStorm::setCurrentScaleCount( float count )
	{
		getIonStorm()->m_currentScaleCount = count;
	}

	types::IonStorm*			 
	IonStorm::getIonStorm( ) const
	{
		return static_cast<types::IonStorm*>( getEntity() );
	}

	void
	IonStorm::allocateReplacement( luabind::detail::object_rep* obj )
	{
		entity_allocate_replacement<IonStorm>( obj, boost::static_pointer_cast<IonStorm>( shared_from_this() ) );
	}
}
