#pragma once

namespace mmm
{
	class ST3D_Colour
	{
	public:
				 ST3D_Colour( );
				 ST3D_Colour( float r, float g, float b );
		explicit ST3D_Colour( unsigned int colour );
		
		const ST3D_Colour operator+( const ST3D_Colour& right ) const;
		const ST3D_Colour operator-( const ST3D_Colour& right ) const;
		const ST3D_Colour operator*( float scale ) const;
		const ST3D_Colour operator/( float scale ) const;

		static ST3D_Colour lerp( const ST3D_Colour& left, const ST3D_Colour& right, float amount );

		float r( ) const;
		float g( ) const;
		float b( ) const;

		void setR( float r );
		void setG( float g );
		void setB( float b );
	private:
		float r_;
		float g_;
		float b_;
	};

	void colour_register( lua_State* state );
	
	std::ostream& operator<<( std::ostream& stream, const ST3D_Colour& color );
}

