#pragma once

namespace mmm
{
	class Path;

	class Camera
	{
	public:
		void	center( const Vector3& position );
		void	center( EntityPtr entity );
		void	center( const Path& path, int index );
		void	zoom( float value );
		Vector3 project( const Vector3& position );
	};

	void camera_register( lua_State* state );
}
