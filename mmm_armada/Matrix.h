#pragma once

#include "Vector3.h"

namespace mmm
{
	//What is the matrix?
	class Matrix
	{
	public:
		Matrix( );
		Matrix( const Matrix& other );
		Matrix& operator=( const Matrix& other );

		//Juicy bits.
		Matrix operator*( const Matrix& other ) const;
		Vector3 operator*( const Vector3& other ) const;

		Matrix transpose() const;

		float get( int row, int column ) const;

		void set( int row, int column, float value );

		//Static initialiser functions for various different
		//types of matrix. Very exciting!
		static Matrix rotationY( float angle );
		static Matrix rotationX( float angle );
		static Matrix rotationZ( float angle );
		static Matrix rotation( float x, float y, float z );
		static Matrix rotation( const Vector3& xyz );
		static Matrix translation( const Vector3& trans );
		static Matrix translation( float x, float y, float z );
		static Matrix scaling( float amount );
		static Matrix scaling( float x, float y, float z );
		static Matrix scaling( const Vector3& amount );
	private:
		float m_[4][4];
	};

	void matrix_register( lua_State* state );
}
