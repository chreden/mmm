// Allows for simpler binding of function pointers from arbitrary
// memory locations.

#pragma once

namespace mmm
{
    // Create a function pointer using the specified memory address.
    template < typename T >
    const T memory_function( std::size_t address )
    {
        T function;
		(*reinterpret_cast<std::size_t*>( &function ) ) = address;
		return function;
    }
}