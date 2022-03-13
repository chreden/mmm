#pragma once

namespace mmm
{
	class Debug
	{
	public:
		bool getDebugDraw( );
		void setDebugDraw( bool value );
		void createConsole( );
		bool getKeyState( const std::string& key );
		void testSound( );
		void circle( const Vector3& centre, float radius, int thickness, ST3D_Colour& colour, void* material );
		void connect( const std::string& ip );
		void disconnect( );
		static Vector3 testCursor();
		std::string getCommandLine() const;
	};

	void debug_register( lua_State* state );
}
