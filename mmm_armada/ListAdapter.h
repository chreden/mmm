#pragma once

namespace mmm
{
	template < typename T >
	class ListAdapter
	{
	public:
		struct Node
		{
			Node* next_;
			Node* prev_;
			T	  value_;
		};
		std::size_t size() const;
		const T&	at( std::size_t index ) const;
	
		char		_allocator_[4];
		Node*		head_;
		std::size_t size_;
	};
}

#include "ListAdapter.inl"
