#include "Team_Internal.h"
#include "Type_Team.h"

namespace mmm
{
	namespace
	{
		const std::size_t Address_SetBiomatter	= 0x00496dd0;
		const std::size_t Address_SetDilithium	= 0x00496ec0;
		const std::size_t Address_SetLatinum	= 0x00496fb0;
		const std::size_t Address_SetMetal		= 0x004970a0;
		const std::size_t Address_GetResource	= 0x00498b00;
	}

	Team::Resources::Resources( types::Team* team )
		: team_( team )
	{

	}

	float
	Team::Resources::getDilithium( ) const
	{
		return getResource( RESOURCE_DILITHIUM );
	}

	float
	Team::Resources::getMetal( ) const
	{
		return getResource( RESOURCE_METAL );
	}

	float
	Team::Resources::getLatinum( ) const
	{
		return getResource( RESOURCE_LATINUM );
	}

	float
	Team::Resources::getBiomatter( ) const
	{
		return getResource( RESOURCE_BIOMATTER );
	}

	float
	Team::Resources::getCrew( ) const
	{
		return getResource( RESOURCE_CREW );
	}
		
	float
	Team::Resources::getResource( eResource resource ) const
	{
		typedef float (types::Team::*GetResourceFunction) ( eResource );
		GetResourceFunction function = memory_function< GetResourceFunction >( Address_GetResource );
		return (team_->*function)( resource );
	}

	void
	Team::Resources::setDilithium( float value )
	{
		typedef void (types::Team::*MemFunction)( float );
		MemFunction function = memory_function< MemFunction >( Address_SetDilithium );
		(team_->*function)( value );
	}

	void
	Team::Resources::setLatinum( float value )
	{
		typedef void (types::Team::*MemFunction)( float );
		MemFunction function = memory_function< MemFunction >( Address_SetLatinum );
		(team_->*function)( value );
	}

	void
	Team::Resources::setMetal( float value )
	{
		typedef void (types::Team::*MemFunction)( float );
		MemFunction function = memory_function< MemFunction >( Address_SetMetal );
		(team_->*function)( value );
	}

	void
	Team::Resources::setBiomatter( float value )
	{
		typedef void (types::Team::*MemFunction)( float );
		MemFunction function = memory_function< MemFunction >( Address_SetBiomatter );
		(team_->*function)( value );
	}

	void
	Team::Resources::setCrew( float value )
	{
		getScriptInterface()->SetTeamCrew( team_->m_teamNumber, value );
	}

	void 
	Team::Resources::setTeam( types::Team* team )
	{
		team_ = team;
	}
}