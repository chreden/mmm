#pragma once

#include "TerrainObject_Internal.h"

namespace mmm
{
	namespace types { struct UtritiumBall; }

	class UtritiumBall
		: public TerrainObject
	{
	public:
		static UtritiumBallPtr create( types::Entity* ent );
		virtual GameObjectClassPtr getClass() const;

		float		getTimeLeft() const;
		EntityPtr	getOwner() const;
		void		setTimeLeft( float value );
	protected:
		explicit	   UtritiumBall( types::UtritiumBall* type );
		virtual void   allocateReplacement( luabind::detail::object_rep* object );
	private:
		types::UtritiumBall* getUtritiumBall() const;
	};

	void utritiumball_register( lua_State* state );
}
