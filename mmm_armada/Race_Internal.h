#pragma once

#include "Type_Race.h"

namespace mmm
{
	class Race
	{
	public:
		explicit Race( types::Race* race );

		static luabind::object getAll();
		static RacePtr		   find( int id );
		static RacePtr		   find( const std::string& name );
		static RacePtr		   create( types::Race* race );

		const std::string getName( ) const;
		const std::string getDisplayName( ) const;
		float			  getBoardingStrength( ) const;
		float			  getRepairStrength( ) const;
		const std::string getSinglePlayerMusic( ) const;
		int				  getNumber() const;

		bool			  isValid() const;

		void			  setSinglePlayerMusic( const std::string& music );
		void			  setDisplayName( const std::string& name );

		types::Race*	  getRace() const;
	private:
		types::Race* race_;
	};

	void race_register( lua_State* state );
}
