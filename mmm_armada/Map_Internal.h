#pragma once

namespace mmm
{
	class Map
	{
	public:
		

        enum eVisibility
        {
            Shrouded = 0,
            Fogged,
            Visible
        };

        
        Vector3 getMin( );
		Vector3 getMax( );
        
        eVisibility getVisibility( const Vector3& position, TeamPtr player ) const;
		
        luabind::object getVisibilityEnum( ) const;

        void    setMin( const Vector3& vec );
		void    setMax( const Vector3& vec );
        


		static void resize( float x, float y );
	private:
		static void updateMapSize();

        mutable luabind::object exploration_;
	};

	void map_register( lua_State* state );
}
