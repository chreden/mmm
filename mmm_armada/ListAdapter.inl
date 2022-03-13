#pragma once

namespace mmm
{
	template< typename T>
	std::size_t
	ListAdapter<T>::size() const
	{
		return size_;
	}

	template< typename T >
	const T&	
	ListAdapter<T>::at( std::size_t index ) const
	{
		Node* current = head_->next_;
		for( int i = 0; i < index, current; ++ i )
		{
			if( i == index )
			{
				return current->value_;
			}
			current = current->next_;
		}
		throw 0;
	}
}
