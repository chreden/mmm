#pragma once

//Resources class manages interaction between lua and the actual Team resources.
namespace mmm
{
	class Team::Resources
		: private NoCopy
	{
	public:
		explicit Resources( types::Team* team );

		float getDilithium() const;
		float getMetal() const;
		float getCrew() const;
		float getLatinum() const;
		float getBiomatter() const;

		void setDilithium( float value );
		void setMetal( float value );
		void setCrew( float value );
		void setLatinum( float value );
		void setBiomatter( float value );

		void setTeam( types::Team* team );
	private:	
		float getResource( eResource resource ) const;

		types::Team* team_;	
	};
}
