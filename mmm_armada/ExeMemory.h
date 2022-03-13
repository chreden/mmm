// Provides access to Armada's memory so memory can be allocated that will
// outlive the DLL instance.

#pragma once

namespace mmm
{
    // Internal settings for integration with Armada's operator new and delete.
    namespace
    {
        // Address of Armada's operator new.
        const std::size_t Address_ExeNew = 0x00652710;
        // Address of Armada's operator delete.
        const std::size_t Address_ExeDelete = 0x006527d0;
        // Operator new for Armada.
        auto exe_operator_new = memory_function< void* (*)(unsigned int) >( Address_ExeNew );
        // Operator delete for Armada.
        auto exe_operator_delete = memory_function< void (*)(void*) >( Address_ExeDelete );
    }

    // Allows access to Armada's operator new, allowing for the allocation of memory in
    // the exe's memory, rather than in the DLL.
    template < typename T >
    T* armada_new( )
    {
        return static_cast<T*>( exe_operator_new( sizeof( T ) ) );
    }

    // Allows access to Armada's operator delete, allowing for the deallocation of memory
    // that was allocated in the exe, rather than in the DLL.
    inline
    void armada_delete( void* ptr )
    {
        exe_operator_delete( ptr );
    }
}
