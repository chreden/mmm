#pragma once

#include "Hook.h"

namespace mmm
{
    class TimerHook : public Hook
    {
    public:
        explicit TimerHook(const std::string& id, int table, int function, int argument);
    };
}
