#pragma once

namespace mmm
{
	template< typename T >
	class VectorAdapter
	{
	public:
		std::size_t size() const;
		const T& operator[]( std::size_t index ) const;
				T& operator[]( std::size_t index );
	public:
		char _allocator_[4];
		T*	 first_;
		T*	 last_;
		T*	 end_;
	};

	class StringAdapter;
	typedef VectorAdapter<StringAdapter > VectorAdapterString;
}

#include "VectorAdapter.inl"
