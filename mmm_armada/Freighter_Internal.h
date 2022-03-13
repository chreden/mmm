#pragma once

#include "Craft_Internal.h"

namespace mmm
{
	namespace types
	{
		class Freighter;
	} 

	class Freighter :
		public Craft
	{
	public:
		static FreighterPtr create( types::Entity* entity );
		eResource getResourceCarried( ) const;
		float	  getSpaceRemaining() const;
		float	  getAmountCarried() const;
		bool	  getDroppingOff() const;
		float	  getMaxAmount( eResource resource ) const;
		float	  getMaxAmountCurrent( ) const;
		EntityPtr getResourceSource() const;
		EntityPtr getStation() const;
			
		void	  setResourceCarried( eResource resource );
		void	  setAmountCarried( float amount );
	protected:
		explicit Freighter( types::Freighter* freighter );
		virtual void allocateReplacement( luabind::detail::object_rep* obj );
	private:
		types::Freighter* getFreighter() const;
	};

	void freighter_register( lua_State* state );
}
