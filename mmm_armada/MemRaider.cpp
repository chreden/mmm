#include "MemRaider.h"

namespace memraider
{
	MrNode::MrNode( std::size_t address )
		: address_( address )
	{
				
	}

	MrNode::MrNode( const void* target )
		: address_( reinterpret_cast<std::size_t>( target ) )
	{

	}

	std::size_t
	MrNode::getAddress( ) const
	{
		return address_;
	}

	void
	MrNode::setAddress( std::size_t address ) 
	{
		address_ = address;
	}

	MrNode
	MrNode::getInner( std::size_t offset ) const
	{
		return MrNode( reinterpret_cast<std::size_t>( *reinterpret_cast<char**>( address_ + offset ) ) );
	}
}