#include "Vector3.h"
#include "Matrix.h"

namespace mmm
{
	void
	vector_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<Vector3>( "Vector" )
				.def( constructor<>() )
				.def( constructor<float,float,float>() )
				.def( "normalize", &Vector3::normalize )
				.def( "dot", &Vector3::dot )
				.def( "cross", &Vector3::cross )
				.def( "lerp", &Vector3::lerp )
				.def( self + other<Vector3>() )
				.def( self - other<Vector3>() )
				.def( self * other<float>() )
				.def( self / other<float>() )
				.def( self * other<Matrix>() )
				.property( "length", &Vector3::length )
				.property( "lengthSquared", &Vector3::lengthSquared )
				.property( "x", &Vector3::x, &Vector3::x )
				.property( "y", &Vector3::y, &Vector3::y )
				.property( "z", &Vector3::z, &Vector3::z )
		];
	}
}
