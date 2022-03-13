#pragma once

namespace memraider
{
	template <typename T>
	T
	MrNode::get( std::size_t offset ) const
	{
		return *reinterpret_cast<T*>( address_ + offset );
	}

	template <typename T>
	void
	MrNode::set( std::size_t offset, const T& value )
	{
		*reinterpret_cast<T*>( address_ + offset ) = value;			
	}

	template <typename T>
	T*
	MrNode::getTarget( ) const
	{
		return reinterpret_cast<T*>( address_ );
	}

	template <typename T>
	void
	MrNode::setTarget( T* target )
	{
		address_ = reinterpret_cast<std::size_t>(target);
	}
}
