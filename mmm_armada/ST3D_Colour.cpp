#include "ST3D_Colour.h"

namespace mmm
{
	ST3D_Colour::ST3D_Colour( )
		: r_( 0 ), g_( 0 ), b_( 0 )
	{

	}

	ST3D_Colour::ST3D_Colour( float r, float g, float b )
		: r_( r ), g_( g ), b_( b )
	{

	}

	ST3D_Colour::ST3D_Colour( unsigned int colour )
		: r_( ((colour & 0xff0000) >> 16) / 255.0f ),
		  g_( ((colour & 0x00ff00 ) >> 8) / 255.0f ),
		  b_( ((colour & 0x0000ff )) / 255.0f )
	{

	}

	const ST3D_Colour 
	ST3D_Colour::operator+( const ST3D_Colour& right ) const
	{
		return ST3D_Colour( r_ + right.r_, g_ + right.g_, b_ + right.b_ );
	}

	const ST3D_Colour
	ST3D_Colour::operator-( const ST3D_Colour& right ) const
	{
		return ST3D_Colour( r_ - right.r_, g_ - right.g_, b_ - right.b_ );
	}

	const ST3D_Colour 
	ST3D_Colour::operator*( float scale ) const
	{
		return ST3D_Colour( r_ * scale, g_ * scale, b_ * scale );
	}

	const ST3D_Colour 
	ST3D_Colour::operator/( float scale ) const
	{
		return ST3D_Colour( r_ / scale, g_ / scale, b_ / scale );
	}

	ST3D_Colour 
	ST3D_Colour::lerp( const ST3D_Colour& left, const ST3D_Colour& right, float amount )
	{
		return ST3D_Colour( left.r_ + (right.r_ - left.r_) * amount,
							left.g_ + (right.g_ - left.g_) * amount,
							left.b_ + (right.b_ - left.b_) * amount );
	}

	float 
	ST3D_Colour::r( ) const
	{
		return r_;
	}

	float 
	ST3D_Colour::g( ) const
	{
		return g_;
	}

	float 
	ST3D_Colour::b( ) const
	{
		return b_;
	}

	void
	ST3D_Colour::setR( float r )
	{
		r_ = r;
	}
	
	void 
	ST3D_Colour::setG( float g )
	{
		g_ = g;
	}
	
	void 
	ST3D_Colour::setB( float b )
	{
		b_ = b;
	}

	std::ostream& 
	operator<<( std::ostream& stream, const ST3D_Colour& color )
	{
		stream << color.r() << "," << color.g() << "," << color.b();
		return stream;
	}

	ST3D_Colour to_colour(lua_State* L, int index)
	{
		const int actual_index = index < 0 ? lua_gettop(L) + index + 1 : index;
		ST3D_Colour colour;
		lua_getfield(L, actual_index, "r");
		colour.setR(lua_tonumber(L, -1));
		lua_getfield(L, actual_index, "g");
		colour.setG(lua_tonumber(L, -1));
		lua_getfield(L, actual_index, "b");
		colour.setB(lua_tonumber(L, -1));
		lua_pop(L, 3);
		return colour;
	}

	int create_colour(lua_State* L, const ST3D_Colour& colour)
	{
		// TODO: Make this the new version of Color
		lua_newtable(L);
		lua_pushnumber(L, colour.r());
		lua_setfield(L, -2, "r");
		lua_pushnumber(L, colour.g());
		lua_setfield(L, -2, "g");
		lua_pushnumber(L, colour.b());
		lua_setfield(L, -2, "b");
		return 1;
	}
}

