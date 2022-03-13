#pragma once

namespace mmm
{
	struct Vector2
	{
		float x, y;
	};

	class Matrix;

	struct Vector3
	{
		explicit Vector3( );
		explicit Vector3( float nX, float nY, float nZ );
			
		float length()			const;
		float lengthSquared()	const;

		const Vector3 normalize() const;
		float		  dot( const Vector3& other ) const;
		const Vector3 cross( const Vector3& other ) const;
		const Vector3 lerp( const Vector3& other, float scalar ) const;

		Vector3 operator+(const Vector3& other) const;
		Vector3 operator-(const Vector3& other) const;
		Vector3 operator*(float other) const;
		Vector3 operator/(float other) const;
		Vector3 operator*(const Matrix& other) const;

		float x, y, z;
	};

	void vector_register( lua_State* state );
}
