#include "Bullet.h"

namespace mmm
{
	void
	bullet_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<Bullet, Ordnance, EntityPtr>( "Bullet" )
				.property("startPosition", &Bullet::getStartPosition )
				.property("currentPosition", &Bullet::getCurrentPosition, &Bullet::setCurrentPosition ) 
		];
	}
}
