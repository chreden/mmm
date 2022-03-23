#pragma once

#include "DebuggerConnection.h"

namespace mmm
{
    namespace print
    {
        /// <summary>
        /// Add a print message to the next available message slot.
        /// </summary>
        /// <param name="message">The message to show.</param>
        /// <param name="type">Type for MMM debugger.</param>
        void add(const std::string& message, DebuggerConnection::Type type = DebuggerConnection::Type_Message);
        /// <summary>
        /// Clear all message slots.
        /// </summary>
        void clear();
    }
}
