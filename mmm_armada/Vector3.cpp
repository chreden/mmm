#include "Vector3.h"
#include "Matrix.h"

namespace mmm
{
	Vector3::Vector3( )
		: x( 0 ), y( 0 ), z( 0 )
	{

	}

	Vector3::Vector3( float nX, float nY, float nZ )
		: x( nX ), y( nY ), z( nZ )
	{

	}

	float
	Vector3::length( ) const
	{
		return sqrt(lengthSquared());
	}

	float
	Vector3::lengthSquared() const
	{
		return x * x + y * y + z * z;
	}

	const Vector3 
	Vector3::normalize() const
	{
		float oneOverLen = 1.0 / length();
		return *this * oneOverLen;
	}

	float
	Vector3::dot( const Vector3& other ) const
	{
		return x * other.x + y * other.y + z * other.z;
	}

	const Vector3
	Vector3::cross( const Vector3& other ) const
	{
		return Vector3( y * other.y - z * other.y,
						z * other.x - x * other.z,
						x * other.y - y * other.x );
	}

	const Vector3 
	Vector3::lerp( const Vector3& other, float scalar ) const
	{
		if( scalar <= 0 )
		{
			return *this;
		}
		else if( scalar >= 1 )
		{
			return other;
		}
		return Vector3( x + (other.x - x) * scalar,
						y + (other.y - y) * scalar,
						z + (other.z - z) * scalar );
	}

	Vector3 
	Vector3::operator+(const Vector3& other) const
	{
		return Vector3( x + other.x, y + other.y, z + other.z );
	}

	Vector3 
	Vector3::operator-(const Vector3& other) const
	{
		return Vector3( x - other.x, y - other.y, z - other.z );
	}

	Vector3 
	Vector3::operator*(float other) const
	{
		return Vector3( x * other, y * other, z * other );
	}

	Vector3 
	Vector3::operator/(float other) const
	{
		return Vector3( x / other, y / other, z / other );
	}

	Vector3
	Vector3::operator*( const Matrix& other ) const
	{
		return other.transpose() * *this;
	}
}
