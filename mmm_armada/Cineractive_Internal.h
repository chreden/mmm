#pragma once

namespace mmm
{
	namespace types
	{
		struct GameObject;
	}

	enum FadeType
	{
		FADE_TYPE_BLACK = 0,
		FADE_TYPE_WHITE
	};

	class Path;

	class Cineractive
	{
	public:
		static void internal_begin( );
		static void internal_end( bool forced );

			 Cineractive( );
		void begin( );
		void end( );
		void forceEnd();
		bool isActive( );
		bool isSkippable( ) const;
		void setActive( bool value );
		void setSkippable( bool value );
		void lookAt( EntityPtr obj );
		void lookAt( const Vector3& pos );
		void lookFrom( const Vector3& pos );
		void lookFrom( EntityPtr object );
		void lookFrom( const Path& path, float speed );
		void setCameraOffset( const Vector3& pos );
		void fadeIn( float time );
		void fadeOut( float time );
	};

	void cineractive_register( lua_State* state );
}
