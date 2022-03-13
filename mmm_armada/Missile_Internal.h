#pragma once

#include "Ordnance.h"

//An aside - unitorped is derived from missile

namespace mmm
{
	namespace types { struct Missile; }

	class Missile
		: public Ordnance
	{
	public:
		static MissilePtr create( types::Entity* entity );
		virtual	~Missile(){};

		Vector3 getOmega() const;
		float	getSeekTimer() const;
		float	getTurnLim2() const;

		void setOmega( const Vector3& value );
		void setTurnLim2( float value );
	protected:
		explicit	   Missile( types::Missile* missile );
		virtual void   allocateReplacement( luabind::detail::object_rep* object );
		types::Missile* getMissile() const;
	};

	void missile_register( lua_State* state );
}
