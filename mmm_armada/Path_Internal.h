#pragma once

namespace mmm
{
	namespace types { struct AiPath; }

	class Path
	{
	public:
        explicit Path( );
		explicit Path( const std::string& name );
		explicit Path( types::AiPath* path );

		const std::string getName() const;
		int				  count( ) const;
		const Vector3	  getPoint( int index ) const;
		bool			  setPoint( int index, const Vector3& point );
		void			  appendPoint( const Vector3& point );
		void			  prependPoint( const Vector3& point );
		void			  setSize( int size );
		void			  remove( int index );

		luabind::object   getPoints() const;

		types::AiPath*	  getPath() const; 
	private:
		static types::AiPath* get( const std::string& name );
		types::AiPath* path_;
	};

	void path_register( lua_State* state );
}