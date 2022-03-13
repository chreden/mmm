#pragma once

#include <cstddef>

namespace memraider
{
	/**
		Manages a pointer.
	*/
	class MrNode
	{
	public:
		/**
			Create a new node representing the data at the specified address
			@param address The address of the data to create this node for
		*/
		explicit MrNode( std::size_t address );
		/**
			Create a new node representing the passed pointer
			@param target The target pointer
		*/
		explicit MrNode( const void* target );
		/**
			Get where this node is pointing.
			@return The target address
		*/
		std::size_t getAddress( ) const;
		/**
			Set the address this node is using.
			@param address The pointer value.
		*/
		void setAddress( std::size_t address );
		/**
			Get the pointer this node is using.
			@return The pointer
		*/
		template < typename T >
		T* getTarget( ) const;
		/**
			Set the pointer for this node
			@param target The new target pointer
		*/
		template < typename T >
		void setTarget( T* target ); 
		/**
			Get an inner node at the specified offset within the target pointer
			@param offset The offset within the pointed to object of the target to get
			@return A new MrNode for this inner object.
		*/
		MrNode getInner( std::size_t offset = 0 ) const;
		/**
			Get the the at the specified address.
			@param offset The offset from the start of the object
		*/
		template < typename T >
		T get( std::size_t offset = 0  ) const;
		/**
			Set the value at the specified address
			@param offset The offset from the start of the object
			@param value The value to use.
		*/
		template < typename T >
		void set( std::size_t offset, const T& value );
	private:
		std::size_t address_;
	};
}

#include "MemRaider.inl"

