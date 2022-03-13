#pragma once

#include "GameObject_Internal.h"

namespace mmm
{
	namespace types 
	{
		struct Craft;
	}

	class Craft : public GameObject
	{
	public:
		static CraftPtr			create( types::Entity* entity );
		const std::string		getName(  ) const;
		float					getShields(  ) const;
		float					getShieldsValue(  ) const;
		float					getMaxShields(  ) const;
		eAlertStatus			getAlertStatus(  ) const;
		eSpecialWeaponAutonomy  getSpecialWeaponAutonomy(  ) const;
		eMovementAutonomy		getMovementAutonomy(  ) const;
		float					getImpulseSpeed() const;
		float					getCrew( ) const;
		float					getMaxCrew( ) const;
		luabind::object			getSystems();
		virtual GameObjectClassPtr getClass() const;
		void					setName( const std::string& name );
		void					setShields( float percentage );
		void					setShieldsValue( float value );
		void					setMaxShields( float value );
		void					setCrew( float value );
		void					setMaxCrew( float value );
		void					setAlertStatus( eAlertStatus status );
		void					setSpecialWeaponAutonomy( eSpecialWeaponAutonomy autonomy );
		void					setMovementAutonomy( eMovementAutonomy autonomy );
		void					setSystemStatus( eCraftSystem system, bool state );
		void					setImpulseSpeed( float value );
		void					explode( );
		void					disableSystem( eCraftSystem system, float time );
		types::Craft*			getCraft() const;
	protected:
		explicit	 Craft( types::Craft* craft );
		virtual void allocateReplacement( luabind::detail::object_rep* obj );
	};

	typedef boost::shared_ptr<Craft> CraftPtr;

	void craft_register( lua_State* state );
}
