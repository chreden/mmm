#include "TimerHook.h"

namespace mmm
{
    TimerHook::TimerHook(const std::string& id, int table, int function, int argument )
        : Hook(id, table, function, argument)
    {
    }
}
