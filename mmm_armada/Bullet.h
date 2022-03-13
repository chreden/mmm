#pragma once
	
#include "Ordnance.h"

namespace mmm
{
	namespace types { struct Bullet; }

	class Bullet
		: public Ordnance
	{
	public:
		static BulletPtr create( types::Entity* entity );

		virtual	~Bullet(){};

		Vector3 getStartPosition() const;
		Vector3 getCurrentPosition() const;

		void setStartPosition( const Vector3& position );
		void setCurrentPosition( const Vector3& position );

	protected:
		explicit Bullet( types::Bullet* bullet );
		virtual void   allocateReplacement( luabind::detail::object_rep* object );
	private:
		types::Bullet* getBullet() const;

	};

	void bullet_register( lua_State* state );
}