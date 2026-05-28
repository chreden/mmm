#pragma once

#include <memory>

namespace mmm
{
    class NoCopy
    {
    protected:
        NoCopy() { };
    private:
        NoCopy( const NoCopy& ){ };
        NoCopy& operator=( const NoCopy& ) { };
    };
}
