#pragma once

#include "Entity_Internal.h"

namespace mmm
{
	namespace types
	{
		struct Ordnance;
	}

	class Ordnance
		: public Entity
	{
	public:
		explicit Ordnance( types::Ordnance* ordnance );
		virtual	~Ordnance(){};

		TeamPtr		getTeam() const;
		Vector3		getTargetLocation() const;
		bool		getReflected() const;
		EntityPtr	getOwner() const;
		EntityPtr	getTarget() const;
		float		getLifetime() const;
		Vector3		getVelocity() const;
		OrdnanceDamagePtr getDamage() const;

		void		setTarget( EntityPtr target );
		void		setLifetime( float value );
		void		setVelocity( const Vector3& value );
		

		types::Ordnance* getOrdnance() const;
	protected:
		virtual void   allocateReplacement( luabind::detail::object_rep* object );
	};

	void ordnance_register( lua_State* state );
}
