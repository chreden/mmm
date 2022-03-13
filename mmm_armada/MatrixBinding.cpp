#include "Matrix.h"

namespace mmm
{
	void
	matrix_register( lua_State* state )
	{
		using namespace luabind;

		module(state)
		[
			class_<Matrix>( "Matrix" )
				.def( constructor<>( ) )
				.def( self * other<Vector3>() )
				.def( self * other<Matrix>() )
				.def( "transpose", &Matrix::transpose )
				.def( "get", &Matrix::get )
				.def( "set", &Matrix::set )
				.scope
				[
					def("rotationY", &Matrix::rotationY ),
					def("rotationX", &Matrix::rotationX ),
					def("rotationZ", &Matrix::rotationZ ),
					def("rotation", (Matrix (*)(float, float, float)) &Matrix::rotation ),
					def("rotation", (Matrix (*)(const Vector3&)) &Matrix::rotation ),
					def("translation", (Matrix (*)(float, float, float)) &Matrix::translation ),
					def("translation", (Matrix (*)(const Vector3&)) &Matrix::translation ),
					def("scaling", (Matrix (*)(float)) &Matrix::scaling ),
					def("scaling", (Matrix (*)(float, float, float)) &Matrix::scaling ),
					def("scaling", (Matrix (*)(const Vector3&)) &Matrix::scaling )
				]
		];
	}
}
