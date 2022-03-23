#include "PrintMessages.h"
#include "UI_Internal.h"
#include "DebuggerConnection.h"
#include <array>

namespace mmm
{
    namespace print
    {
        namespace
        {
            /// <summary>
            /// A print message slot - may or may not contain a message.
            /// </summary>
            struct Message
            {
                static constexpr int Invalid = -1;
                int id = Invalid;

                /// <summary>
                /// Whether the message slot is in use.
                /// </summary>
                constexpr bool valid() const noexcept
                {
                    return id != Invalid;
                }

                /// <summary>
                /// Clear the message slot.
                /// </summary>
                void remove()
                {
                    if (!valid())
                    {
                        return;
                    }

                    UI().removeMessage(id);
                    id = Invalid;
                }

                /// <summary>
                /// Set the contents of the message slot.
                /// </summary>
                /// <param name="message">The message value.</param>
                /// <param name="index">The index used for placement.</param>
                void set(const std::string& message, int index)
                {
                    id = UI().addMessage(message, 50, 50 + 30 * index, JUSTIFY_TOP_LEFT, ST3D_Colour(0xffffffff), false, 1e6);
                }
            };

            std::array<Message, 20> messages;
            int32_t current_index{ 0 };

            /// <summary>
            /// Find the next available message slot.
            /// </summary>
            std::size_t next_index() noexcept
            {
                if (current_index == messages.size())
                {
                    clear();
                }
                return current_index++;
            }
        }

        void add(const std::string& message, DebuggerConnection::Type type)
        {
            if (DebuggerConnection::getInstance().connected())
            {
                DebuggerConnection::getInstance().sendMessage(message, type);
            }
            else
            {
                std::size_t newIndex = next_index();
                if (messages[newIndex].valid())
                {
                    messages[newIndex].remove();
                }
                messages[newIndex].set(message, newIndex);
            }
        }

        void clear()
        {
            current_index = 0;
            std::for_each(messages.begin(), messages.end(), [](auto&& m) { m.remove(); });
        }
    }
}
