#pragma once

namespace mmm
{
	template< typename T >
	std::size_t
	VectorAdapter<T>::size() const
	{
		return last_ - first_;
	}

	template< typename T >
	const T&
	VectorAdapter<T>::operator[]( std::size_t index ) const
	{
		return *(first_ + index);
	}

	template < typename T >
	T&
	VectorAdapter<T>::operator[]( std::size_t index )
	{
		return *(first_ + index);
	}
}
