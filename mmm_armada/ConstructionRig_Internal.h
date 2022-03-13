#pragma once

#include "Producer.h"

namespace mmm
{
	namespace types
	{
		struct ConstructionRig;
	}

	class ConstructionRig 
		: public Producer
	{
	public:
		static ConstructionRigPtr create( types::Entity* entity );

		int		  getBeesOnboard() const;
		EntityPtr getConstructionObject() const;

		void	  setBeesOnboard( int value );
	protected:
		explicit ConstructionRig( types::ConstructionRig* producer );
		virtual void allocateReplacement( luabind::detail::object_rep* object );
	private:
		types::ConstructionRig* getConstructionRig() const;
	};

	void constructionrig_register( lua_State* state );
}
