#pragma once

namespace mmm
{
	class Media
	{
	public:
		void playSound( const std::string& filename );
		void playMusic( const std::string& filename );
		void playMovie( const std::string& filename );
		void stopMovie( );
		void stopMusic( );
		void stopSounds( );
		
		static void update( );
	};

	void media_register( lua_State* state );
}
