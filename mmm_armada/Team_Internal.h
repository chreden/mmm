#pragma once

namespace mmm
{
	namespace types { class Team; }

	enum eTradeDirection
	{
		TradeDir_To = 0,
		TradeDir_From
	};

	class Race;
	class Team
		: private NoCopy
	{
	public:
		explicit	  Team( int teamNumber );
		explicit	  Team( types::Team* team );
		float		  getResource( eResource resource ) const;
		eTeamRelation getRelation( TeamPtr other ) const;
		int			  getMaxOfficers( ) const;
		float		  getMaxCrew( ) const;
		void		  getEntities( std::vector<EntityPtr>& out ) const;
		ST3D_Colour   getColor( ) const;
		int			  getNumber( ) const;
		float		  getAmountTraded( eResource resource, eTradeDirection direction, TeamPtr other ) const;
		eSlotType	  getSlotType( ) const;
		RacePtr		  getRace( ) const;
		bool		  getIsAI( ) const;

		void		  setColor( const ST3D_Colour& color );
		void		  setResource( eResource resource, float amount, bool relative );
		void		  setRelation( TeamPtr other, eTeamRelation relation );
		void		  setMaxOfficers( int value );
		void		  setMaxCrew( float value );
		void		  setIsAI( bool value );
		void		  loadAIP( const std::string& aip );

		const std::string getName() const;
		void			  setName( const std::string& name );

		bool			 isValid() const;


		class Resources;
		typedef boost::shared_ptr<Resources> ResourcesPtr;

		ResourcesPtr	getResources() const;
	private:
		types::Team* team_;
		//The resources class simply forwards things on.
		ResourcesPtr resources_;
	};
	
	void team_register( lua_State* state );
}

#include "Team_Resources.h"