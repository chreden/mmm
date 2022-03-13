#include "ST3D_Colour.h"

namespace mmm
{
	void
	colour_register( lua_State* state )
	{
		using namespace luabind;

		module( state )
		[
			class_< ST3D_Colour >( "Color" )
				.def( constructor<>() )
				.def( constructor<unsigned int>() )
				.def( constructor<float, float, float>() )
				.def( self + other<ST3D_Colour>() )
				.def( self - other<ST3D_Colour>() )
				.def( self * other<float>() )
				.def( self / other<float>() )
				.property( "r", &ST3D_Colour::r, &ST3D_Colour::setR )
				.property( "g", &ST3D_Colour::g, &ST3D_Colour::setG )
				.property( "b", &ST3D_Colour::b, &ST3D_Colour::setB )
				.def(tostring(self))
				.scope
				[
					def( "lerp", &ST3D_Colour::lerp )
				]
		];
	}
}
